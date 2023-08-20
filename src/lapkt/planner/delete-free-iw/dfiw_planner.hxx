#ifndef __DFIW_PLANNER__
#define __DFIW_PLANNER__

#include <lapkt/planner/planner.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/node_eval/novelty/novelty.hxx>
#include <lapkt/engine/iw.hxx>

#include <lapkt/model/strips_state.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_graph.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_graph_generator.hxx>
#include <lapkt/engine/node_eval/heuristic/h_2.hxx>

#include <lapkt/utils/string_conversions.hxx>

#include <iostream>
#include <fstream>

class DFIW_Planner : public Planner
{
public:
	typedef aptk::search::brfs::Node<
			aptk::State>
			IW_Node;
	typedef aptk::agnostic::Novelty<
			aptk::agnostic::Fwd_Search_Problem, IW_Node>
			H_Novel_Fwd;
	typedef aptk::search::brfs::IW<
			aptk::agnostic::Fwd_Search_Problem, H_Novel_Fwd>
			IW_Fwd;

	DFIW_Planner();
	virtual ~DFIW_Planner();

	void setup();
	void solve();

	int m_iw_bound;
	std::string m_log_filename;
	std::string m_plan_filename;

protected:
	float do_search(IW_Fwd &engine);
	aptk::STRIPS_Problem m_df_relaxation;
};

#endif
