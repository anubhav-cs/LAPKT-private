#ifndef __BFS_F_PLANNER__
#define __BFS_F_PLANNER__

#include <lapkt/planner/planner.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/node_eval/novelty/novelty_partition.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_graph.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_graph_generator.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_graph_manager.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_count.hxx>
#include <lapkt/engine/node_eval/heuristic/h_2.hxx>
#include <lapkt/engine/node_eval/heuristic/h_1.hxx>
#include <lapkt/engine/node_eval/heuristic/rp_heuristic.hxx>
#include <fstream>

#include <lapkt/engine/open_list.hxx>
#include <lapkt/engine/at_gbfs_3h.hxx>
using aptk::Action;
using aptk::agnostic::Fwd_Search_Problem;

using aptk::agnostic::Landmarks_Count_Heuristic;
using aptk::agnostic::Landmarks_Graph;
using aptk::agnostic::Landmarks_Graph_Generator;
using aptk::agnostic::Landmarks_Graph_Manager;

using aptk::agnostic::H1_Heuristic;
using aptk::agnostic::H2_Heuristic;
using aptk::agnostic::H_Add_Evaluation_Function;
using aptk::agnostic::Novelty_Partition;
using aptk::agnostic::Relaxed_Plan_Heuristic;

using aptk::search::Node_Comparer_3H;
using aptk::search::Open_List;
using aptk::search::gbfs_3h::AT_GBFS_3H;
// using	aptk::search::gbfs_mh::Node;

class BFS_f_Planner : public Planner
{
public:
    typedef H2_Heuristic<Fwd_Search_Problem> H2_Fwd;
    typedef Landmarks_Graph_Generator<Fwd_Search_Problem> Gen_Lms_Fwd;
    typedef Landmarks_Count_Heuristic<Fwd_Search_Problem> H_Lmcount_Fwd;
    typedef Landmarks_Graph_Manager<Fwd_Search_Problem> Land_Graph_Man;

    // MRJ: We start defining the type of nodes for our planner
    typedef aptk::search::gbfs_3h::Node<Fwd_Search_Problem, aptk::State> Search_Node;
    typedef Novelty_Partition<Fwd_Search_Problem, Search_Node> H_Novel_Fwd;

    // MRJ: Then we define the type of the tie-breaking algorithm
    // for the open list we are going to use
    typedef Node_Comparer_3H<Search_Node> Tie_Breaking_Algorithm;

    // MRJ: Now we define the Open List type by combining the types we have defined before
    typedef Open_List<Tie_Breaking_Algorithm, Search_Node> BFS_Open_List;

    // MRJ: Now we define the heuristics
    typedef H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function> H_Add_Fwd; //, aptk::agnostic::H1_Cost_Function::Ignore_Costs
    typedef Relaxed_Plan_Heuristic<Fwd_Search_Problem, H_Add_Fwd> H_Add_Rp_Fwd;

    // MRJ: Now we're ready to define the BFS algorithm we're going to use
    typedef AT_GBFS_3H<Fwd_Search_Problem, H_Novel_Fwd, H_Lmcount_Fwd, H_Add_Rp_Fwd, BFS_Open_List> Anytime_GBFS_H_Add_Rp_Fwd;

    BFS_f_Planner();
    virtual ~BFS_f_Planner();

    void setup();
    void solve();

    int m_max_novelty;
    std::string m_log_filename;
    std::string m_plan_filename;
    bool m_one_ha_per_fluent;

protected:
    float do_search(Anytime_GBFS_H_Add_Rp_Fwd &engine);
};

#endif
