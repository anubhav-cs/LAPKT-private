#ifndef __BRFS_PLANNER__
#define __BRFS_PLANNER__

#include <lapkt/planner/planner.hxx>
#include <lapkt/model/fwd_search_prob.hxx>
#include <lapkt/engine/brfs.hxx>

using aptk::Action;
using aptk::agnostic::Fwd_Search_Problem;

using aptk::search::brfs::BRFS;

class BRFS_Planner : public Planner
{
public:
	// NIR: Now we're ready to define the BRFS algorithm
	typedef BRFS<Fwd_Search_Problem> BRFS_Fwd;

	BRFS_Planner();
	virtual ~BRFS_Planner();

	void setup();
	void solve();

	std::string m_log_filename;
	std::string m_plan_filename;

protected:
	float do_search(BRFS_Fwd &engine);
};

#endif
