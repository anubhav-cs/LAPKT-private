#ifndef __DFSIW_PLANNER__
#define __DFSIW_PLANNER__

#include <planner.hxx>
#include <fwd_search_prob.hxx>
#include <novelty.hxx>
#include <siw.hxx>

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
