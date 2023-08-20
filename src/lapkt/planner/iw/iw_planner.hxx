#ifndef __IW_PLANNER__
#define __IW_PLANNER__

//---- CONSTANTS
#define IW_BOUND 2
#define LOG_FILE "planner.log"
#define PLAN_FILE "plan.ipc"

// Standard library
#include <iostream>
#include <fstream>

// LAPKT specific
#include <lapkt/planner/planner.hxx>
#include <lapkt/model/strips_prob.hxx>
#include <lapkt/model/strips_state.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/node_eval/novelty/novelty.hxx>
#include <lapkt/engine/node_eval/heuristic/h_2.hxx>
#include <lapkt/engine/node_eval/heuristic/h_1.hxx>
#include <lapkt/engine/iw.hxx>

using aptk::agnostic::Fwd_Search_Problem;

using aptk::agnostic::H1_Heuristic;
using aptk::agnostic::H2_Heuristic;
using aptk::agnostic::H_Max_Evaluation_Function;

using aptk::agnostic::Novelty;
using aptk::search::brfs::IW;

/**
 * @brief Iterative-width planner class
 * 
 */
class IW_Planner : public Planner
{
public:
  typedef aptk::search::brfs::Node<aptk::State> IW_Node;
  typedef Novelty<Fwd_Search_Problem, IW_Node> H_Novel_Fwd;
  typedef H2_Heuristic<Fwd_Search_Problem> H2_Fwd;
  typedef H1_Heuristic<Fwd_Search_Problem, H_Max_Evaluation_Function>
      H1_Fwd;
  typedef IW<Fwd_Search_Problem, H_Novel_Fwd> IW_Fwd;

  IW_Planner();
  virtual ~IW_Planner();

  void setup();
  void solve();

  unsigned m_iw_bound;
  std::string m_log_filename;
  std::string m_plan_filename;
  bool m_atomic = false;

protected:
  template <typename Search_Engine>
  float do_search(Search_Engine &engine,
                  aptk::STRIPS_Problem &plan_prob,
                  std::ofstream &plan_stream);
  template <typename Search_Engine>
  float do_inc_bound_search(Search_Engine &engine,
                            aptk::STRIPS_Problem &plan_prob,
                            std::ofstream &plan_stream);
  template <typename Search_Engine>
  float do_search_single_goal(
      Search_Engine &engine, aptk::STRIPS_Problem &plan_prob,
      std::ofstream &plan_stream);
};
#endif
