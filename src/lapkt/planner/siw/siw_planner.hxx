#ifndef __SIW_PLANNER__
#define __SIW_PLANNER__

#include <lapkt/planner/planner.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/node_eval/novelty/novelty.hxx>
#include <lapkt/engine/siw.hxx>

class SIW_Planner : public Planner
{
public:
	typedef aptk::search::SIW<aptk::agnostic::Fwd_Search_Problem> SIW_Fwd;

	SIW_Planner();
	virtual ~SIW_Planner();

	void setup();
	void solve();

	int m_iw_bound;
	std::string m_log_filename;
	std::string m_plan_filename;

protected:
	float do_search(SIW_Fwd &engine);
};

#endif
