#ifndef __RP_IW_PLANNER__
#define __RP_IW_PLANNER__

#include <lapkt/planner/planner.hxx>
#include <lapkt/model/strips_state.hxx>
#include <lapkt/model/strips_prob.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/node_eval/novelty/novelty_partition.hxx>
#include <lapkt/engine/rp_iw.hxx>
#include <lapkt/engine/node_eval/heuristic/h_1.hxx>
#include <lapkt/engine/node_eval/heuristic/rp_heuristic.hxx>

using aptk::agnostic::Fwd_Search_Problem;

using aptk::agnostic::H1_Heuristic;
using aptk::agnostic::H_Add_Evaluation_Function;
using aptk::agnostic::Relaxed_Plan_Heuristic;

using aptk::agnostic::Novelty_Partition;
using aptk::search::novelty_spaces::RP_IW;

class RPIW_Planner : public Planner
{
public:
	typedef aptk::search::novelty_spaces::Node<aptk::State> IW_Node;
	typedef Novelty_Partition<Fwd_Search_Problem, IW_Node> H_Novel_Fwd;
	typedef H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function> H_Add_Fwd;
	typedef Relaxed_Plan_Heuristic<Fwd_Search_Problem, H_Add_Fwd> H_Add_Rp_Fwd;
	typedef RP_IW<Fwd_Search_Problem, H_Novel_Fwd, H_Add_Rp_Fwd> RP_IW_Fwd;

	RPIW_Planner();
	virtual ~RPIW_Planner();

	void setup();
	void solve();

	int m_iw_bound;
	std::string m_log_filename;
	std::string m_plan_filename;

	bool m_atomic = false;

protected:
	float do_search_single_goal(RP_IW_Fwd &engine, aptk::STRIPS_Problem &plan_prob, std::ofstream &plan_stream);
	float do_search(RP_IW_Fwd &engine, aptk::STRIPS_Problem &plan_prob, std::ofstream &plan_stream);
};

#endif
