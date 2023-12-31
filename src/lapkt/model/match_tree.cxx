/*
Lightweight Automated Planning Toolkit

Copyright 2022
Miquel Ramirez <miquel.ramirez@unimelb.edu.au>Nir Lipovetzky <nirlipo@gmail.com>
Christian Muise <christian.muise@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject
 to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <lapkt/model/match_tree.hxx>
#include <lapkt/model/strips_prob.hxx>
#include <lapkt/model/strips_state.hxx>
#include <lapkt/model/action.hxx>
#include <algorithm>
#include <iostream>

namespace aptk
{

    namespace agnostic
    {

        void Match_Tree::build()
        {
            std::vector<bool> vars_seen(m_problem.fluents().size(), false);
            std::vector<int> actions;

            for (unsigned i = 0; i < m_problem.num_actions(); ++i)
                actions.push_back(i);

            root_node = new SwitchNode(actions, vars_seen, m_problem);
        }

        void Match_Tree::retrieve_applicable(const State &s, std::vector<int> &actions) const
        {
            return root_node->generate_applicable_items(s, actions);
        }

        /********************/

        BaseNode *BaseNode::create_tree(std::vector<int> &actions, std::vector<bool> &vars_seen, const STRIPS_Problem &prob)
        {

            if (actions.empty())
                return new EmptyNode;

            // If every item is done, then we create a leaf node
            bool all_done = true;
            for (unsigned i = 0; all_done && (i < actions.size()); ++i)
            {
                if (!(action_done(actions[i], vars_seen, prob)))
                {
                    all_done = false;
                }
            }

            if (all_done)
            {
                return new LeafNode(actions);
            }
            else
            {
                return new SwitchNode(actions, vars_seen, prob);
            }
        }

        int BaseNode::get_best_var(std::vector<int> &actions, std::vector<bool> &vars_seen, const STRIPS_Problem &prob)
        {

            // TODO: This fluents.size() stuff needs to change to the number of mutexes once they're computed
            static std::vector<int> var_count;
            var_count.resize(prob.fluents().size(), 0);

            int max_size = 0;
            int best_var = 0;
            for (unsigned i = 0; i < actions.size(); ++i)
            {
                const Action *act = prob.actions()[actions[i]];
                for (unsigned j = 0; j < act->prec_varval().size(); ++j)
                {
                    unsigned idx = act->prec_varval()[j].first;
                    var_count[idx]++;
                    if (var_count[idx] > max_size && vars_seen[idx] == false)
                    {
                        max_size = var_count[idx];
                        best_var = idx;
                    }
                }
            }

            // std::cout << "Best var " << best_var << " with a count of " << var_count[best_var] << std::endl;
            return best_var;
        }

        bool BaseNode::action_done(int action_id, std::vector<bool> &vars_seen, const STRIPS_Problem &prob)
        {

            const Action *act = prob.actions()[action_id];

            for (unsigned i = 0; i < act->prec_varval().size(); ++i)
            {
                if (vars_seen[act->prec_varval()[i].first] == false)
                    return false;
            }

            return true;
        }

        /********************/

        void EmptyNode::dump(std::string indent, const STRIPS_Problem &) const
        {
            std::cout << indent << "<empty>" << std::endl;
        }

        /********************/

        LeafNode::LeafNode(std::vector<int> &actions)
        {
            applicable_items.swap(actions);
        }

        void LeafNode::dump(std::string indent, const STRIPS_Problem &prob) const
        {
            for (unsigned i = 0; i < applicable_items.size(); ++i)
                std::cout << indent << prob.actions()[applicable_items[i]]->signature() << std::endl;
        }

        void LeafNode::generate_applicable_items(const State &, std::vector<int> &actions)
        {
            actions.insert(actions.end(), applicable_items.begin(), applicable_items.end());
        }

        /********************/

        void SwitchNode::generate_applicable_items(const State &s, std::vector<int> &actions)
        {
            actions.insert(actions.end(), immediate_items.begin(), immediate_items.end());

            // TODO: Change this when mutex's are done proper
            // children[s.value_for_var(switch_var)]->generate_applicable_items( s, actions );
            if (1 == s.value_for_var(switch_var))
                children[0]->generate_applicable_items(s, actions);

            default_child->generate_applicable_items(s, actions);
        }

        SwitchNode::SwitchNode(std::vector<int> &actions, std::vector<bool> &vars_seen, const STRIPS_Problem &prob)
        {

            switch_var = get_best_var(actions, vars_seen, prob);

            std::vector<std::vector<int>> value_items;
            std::vector<int> default_items;

            // TODO: This should change when the mutex's are computed
            //        Ditto for the "1 == s.value..." and "value_items[0]..." lines below
            int num_of_var_values = 1;

            // Initialize the value_items
            for (int i = 0; i < num_of_var_values; ++i)
                value_items.push_back(std::vector<int>());

            // Sort out the regression items
            for (unsigned i = 0; i < actions.size(); ++i)
            {
                if (action_done(actions[i], vars_seen, prob))
                {
                    immediate_items.push_back(actions[i]);
                }
                else if (prob.actions()[actions[i]]->requires(switch_var))
                {
                    value_items[0].push_back(actions[i]);
                }
                else
                { // == -1
                    default_items.push_back(actions[i]);
                }
            }

            vars_seen[switch_var] = true;

            // Create the switch generators
            for (unsigned i = 0; i < value_items.size(); i++)
            {
                children.push_back(create_tree(value_items[i], vars_seen, prob));
            }

            // Create the default generator
            default_child = create_tree(default_items, vars_seen, prob);

            vars_seen[switch_var] = false;
        }

        void SwitchNode::dump(std::string indent, const STRIPS_Problem &prob) const
        {
            std::cout << indent << "switch on " << prob.fluents()[switch_var]->signature() << std::endl;
            std::cout << indent << "immediately:" << std::endl;
            for (unsigned i = 0; i < immediate_items.size(); ++i)
                std::cout << indent << prob.actions()[immediate_items[i]]->signature() << std::endl;
            for (unsigned i = 0; i < children.size(); ++i)
            {
                std::cout << indent << "case " << i << ":" << std::endl;
                children[i]->dump(indent + "  ", prob);
            }
            std::cout << indent << "always:" << std::endl;
            default_child->dump(indent + "  ", prob);
        }

        int SwitchNode::count() const
        {
            int total = 0;
            for (unsigned i = 0; i < children.size(); ++i)
                total += children[i]->count();
            total += default_child->count();
            total += immediate_items.size();
            return total;
        }

        /********************/

    }

}
