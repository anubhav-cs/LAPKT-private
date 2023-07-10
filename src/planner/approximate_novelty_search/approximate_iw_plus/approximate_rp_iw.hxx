/**
 * @file approximate_rp_iw.hxx
 * @author Anubhav Singh (anubhav.singh.er@pm.me)
 * @author Miquel Ramirez (miquel.ramirez@unimelb.edu.au)
 * @author Nir Lipovetzky (nirlipo@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
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

#ifndef __APPROXIMATE_IW_PLUS__
#define __APPROXIMATE_IW_PLUS__

//---- CONSTANTS
#define IW_BOUND 2
#define LOG_FILE "planner.log"
#define PLAN_FILE "plan.ipc"

// Standard library
#include <iostream>
#include <fstream>

// LAPKT specific
#include <py_strips_interface.hxx>
#include <strips_prob.hxx>
#include <strips_state.hxx>
#include <fwd_search_prob.hxx>
#include "approximate_novelty_partition_1.hxx"
#include <h_2.hxx>
#include <h_1.hxx>
#include <rp_heuristic.hxx>
#include "approx_novelty_rp_iw.hxx"

using aptk::agnostic::Fwd_Search_Problem;

using aptk::agnostic::H1_Heuristic;
using aptk::agnostic::H2_Heuristic;
using aptk::agnostic::H_Add_Evaluation_Function;
using aptk::agnostic::H_Max_Evaluation_Function;
using aptk::agnostic::Relaxed_Plan_Heuristic;

using aptk::agnostic::Approximate_Novelty_Partition;
using aptk::search::novelty_spaces::Approximate_RP_IW_Search;

//---- Approximate_RP_IW Class -----------------------------------------------------//
class Approximate_RP_IW : public STRIPS_Interface
{

        typedef aptk::search::novelty_spaces::Node<aptk::State> IW_Node;
        typedef Approximate_Novelty_Partition<Fwd_Search_Problem, IW_Node> H_Novel_Fwd;
        typedef H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function> H_Add_Fwd;
        typedef Relaxed_Plan_Heuristic<Fwd_Search_Problem, H_Add_Fwd> H_Add_Rp_Fwd;
        typedef Approximate_RP_IW_Search<Fwd_Search_Problem, H_Novel_Fwd, H_Add_Rp_Fwd> RP_IW_Fwd;

public:
        Approximate_RP_IW();
        Approximate_RP_IW(std::string, std::string);
        Approximate_RP_IW(std::string, std::string, unsigned,
                          std::string, std::string);
        virtual ~Approximate_RP_IW();

        virtual void setup(bool gen_match_tree = true);
        void solve();

        unsigned m_iw_bound;
        std::string m_log_filename;
        std::string m_plan_filename;
        float m_sampling_factor;
        std::string m_sampling_strategy;
        unsigned m_rand_seed;
        unsigned m_min_k4sample;

protected:
        template <typename Search_Engine>
        float do_search(Search_Engine &engine,
                        aptk::STRIPS_Problem &plan_prob,
                        std::ofstream &plan_stream);
        template <typename Search_Engine>
        float do_inc_bound_search(Search_Engine &engine,
                                  aptk::STRIPS_Problem &plan_prob,
                                  std::ofstream &plan_stream);
};
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//
#endif
