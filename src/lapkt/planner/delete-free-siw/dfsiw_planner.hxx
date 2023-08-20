#ifndef __DFSIW_PLANNER__
#define __DFSIW_PLANNER__

#include <lapkt/planner/planner.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/node_eval/novelty/novelty.hxx>
#include <lapkt/engine/siw.hxx>

#include <lapkt/model/strips_state.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_graph.hxx>
#include <lapkt/engine/node_eval/heuristic/landmark_graph_generator.hxx>
#include <lapkt/engine/node_eval/heuristic/h_2.hxx>

#include <lapkt/engine/iw.hxx>
#include <lapkt/engine/serialized_search.hxx>
#include <lapkt/utils/string_conversions.hxx>

#include <iostream>
#include <fstream>

class DFSIW_Planner : public Planner
{
public:
	typedef aptk::search::SIW<aptk::agnostic::Fwd_Search_Problem> SIW_Fwd;

	DFSIW_Planner();
	virtual ~DFSIW_Planner();

	void setup();
	void solve();

	int m_iw_bound;
	std::string m_log_filename;
	std::string m_plan_filename;

protected:
	float do_search(SIW_Fwd &engine);

protected:
	aptk::STRIPS_Problem m_df_relaxation;
};

#endif
