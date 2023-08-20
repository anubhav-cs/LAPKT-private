#ifndef __SIW_PLUS_PLANNER__
#define __SIW_PLUS_PLANNER__

#include <lapkt/planner/planner.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/node_eval/novelty/novelty.hxx>
#include <lapkt/engine/node_eval/novelty/novelty_partition.hxx>
#include <lapkt/engine/node_eval/heuristic/h_1.hxx>
#include <lapkt/engine/node_eval/heuristic/rp_heuristic.hxx>

#include <lapkt/engine/rp_iw.hxx>
#include <lapkt/engine/siw_plus.hxx>
#include <lapkt/engine/serialized_search.hxx>

using aptk::agnostic::Fwd_Search_Problem;
using aptk::agnostic::H1_Heuristic;
using aptk::agnostic::H_Add_Evaluation_Function;
using aptk::agnostic::Relaxed_Plan_Heuristic;

using aptk::agnostic::Novelty;
using aptk::agnostic::Novelty_Partition;
using aptk::search::Serialized_Search;
using aptk::search::novelty_spaces::RP_IW;
using aptk::search::novelty_spaces::SIW_Plus;

class SIW_Plus_Planner : public Planner
{
public:
	typedef aptk::search::novelty_spaces::Node<aptk::State> IW_Node;
	typedef Novelty_Partition<Fwd_Search_Problem, IW_Node> H_Novel_Fwd;

	typedef H1_Heuristic<Fwd_Search_Problem, H_Add_Evaluation_Function> H_Add_Fwd;
	typedef Relaxed_Plan_Heuristic<Fwd_Search_Problem, H_Add_Fwd> H_Add_Rp_Fwd;

	typedef RP_IW<Fwd_Search_Problem, H_Novel_Fwd, H_Add_Rp_Fwd> RP_IW_Fwd;
	typedef SIW_Plus<Fwd_Search_Problem> SIW_Plus_Fwd;

	SIW_Plus_Planner();
	virtual ~SIW_Plus_Planner();

	void setup();
	void solve();

	int m_iw_bound;
	std::string m_log_filename;
	std::string m_plan_filename;

protected:
	float do_search(SIW_Plus_Fwd &engine);
};

#endif
