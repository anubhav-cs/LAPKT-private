#include <anytime_lapkt.hxx>
using namespace boost::python;

BOOST_PYTHON_MODULE( libatlapkt )
{
	class_<AT_LAPKT_Planner>("AT_LAPKT_Planner")
		.def( init< std::string, std::string >() )
		.def( "add_atom", &AT_LAPKT_Planner::add_atom )
		.def( "add_action", &AT_LAPKT_Planner::add_action )
		.def( "add_mutex_group", &AT_LAPKT_Planner::add_mutex_group )
		.def( "num_atoms", &AT_LAPKT_Planner::n_atoms )
		.def( "num_actions", &AT_LAPKT_Planner::n_actions )
		.def( "get_atom_name", &AT_LAPKT_Planner::get_atom_name )
		.def( "get_domain_name", &AT_LAPKT_Planner::get_domain_name )
		.def( "get_problem_name", &AT_LAPKT_Planner::get_problem_name )
		.def( "add_precondition", &AT_LAPKT_Planner::add_precondition )
		.def( "add_effect", &AT_LAPKT_Planner::add_effect )
		.def( "add_cond_effect", &AT_LAPKT_Planner::add_cond_effect )
		.def( "set_cost", &AT_LAPKT_Planner::set_cost )
		.def( "notify_negated_conditions", &AT_LAPKT_Planner::notify_negated_conditions )
		.def( "create_negated_fluents", &AT_LAPKT_Planner::create_negated_fluents )
		.def( "set_init", &AT_LAPKT_Planner::set_init )
		.def( "set_goal", &AT_LAPKT_Planner::set_goal )
		.def( "set_domain_name", &AT_LAPKT_Planner::set_domain_name )
		.def( "set_problem_name", &AT_LAPKT_Planner::set_problem_name )
		.def( "write_ground_pddl", &AT_LAPKT_Planner::write_ground_pddl )
		.def( "print_action", &AT_LAPKT_Planner::print_action )
		.def( "setup", &AT_LAPKT_Planner::setup )
		.def( "solve", &AT_LAPKT_Planner::solve )
		.def_readwrite( "ignore_action_costs", &AT_LAPKT_Planner::m_ignore_action_costs )
		.def_readwrite( "parsing_time", &AT_LAPKT_Planner::m_parsing_time )
		.def_readwrite( "iw_bound", &AT_LAPKT_Planner::m_iw_bound )
		.def_readwrite( "max_novelty", &AT_LAPKT_Planner::m_max_novelty )
		.def_readwrite( "log_filename", &AT_LAPKT_Planner::m_log_filename )
		.def_readwrite( "enable_siw_plus", &AT_LAPKT_Planner::m_enable_siw_plus )
		.def_readwrite( "enable_bfs_f", &AT_LAPKT_Planner::m_enable_bfs_f )
	;
}

