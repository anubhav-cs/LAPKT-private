file(WRITE ${PROJECT_BINARY_DIR}/${REL_PYPI_LAPKT_ROOT}/planner/lapkt_planner_config.yml "")

add_subdirectory(apx_bfws)
add_subdirectory(apx_dfs_plus)
add_subdirectory(apx_iw)
add_subdirectory(apx_iw_plus)
add_subdirectory(apx_siw)
add_subdirectory(anytime_lapkt)
add_subdirectory(at_bfs_f)
add_subdirectory(bfs_f)
add_subdirectory(brfs)
add_subdirectory(bfws)
add_subdirectory(delete-free-iw)
add_subdirectory(delete-free-siw)
add_subdirectory(dfs_plus)
add_subdirectory(iw)
add_subdirectory(iw_plus)
add_subdirectory(siw)
add_subdirectory(siw_plus)
add_subdirectory(siw_plus-then-bfs_f)

install(
  FILES
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/anytime_lapkt/anytime_lapkt.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/at_bfs_f/at_bfsf_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/bfs_f/bfsf_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/bfws/bfws.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/brfs/brfs_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/bfws/bfws.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/delete-free-iw/dfiw_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/delete-free-siw/dfsiw_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/dfs_plus/dfs_plus_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/iw/iw_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/iw_plus/rp_iw_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/siw/siw_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/siw_plus/siw_plus_planner.hxx
    # ${PROJECT_SOURCE_DIR}/src/lapkt/planner/siw_plus-then-bfs_f/siw_plus_bfs_f.hxx
    ${PROJECT_SOURCE_DIR}/src/lapkt/planner/planner.hxx
  DESTINATION
    ${CMAKE_INSTALL_PREFIX}/${REL_CORE_INC_DIR}/lapkt/planner
  COMPONENT
    lapkt
)

# PUBLIC_HEADER files can be installed with 
#   install(<target> ...PUBLIC_HEADER DESTINATION ...)

# set_target_properties(planner PROPERTIES
#     PUBLIC_HEADER
# "${PROJECT_SOURCE_DIR}/src/lapkt/planner/anytime_lapkt/anytime_lapkt.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/anytime_lapkt/ipc2014_rwa.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/at_bfs_f/at_bfsf_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/bfs_f/bfsf_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/bfws/bfws.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/brfs/brfs_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/bfws/bfws.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/delete-free-iw/dfiw_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/delete-free-siw/dfsiw_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/dfs_plus/dfs_plus_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/iw/iw_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/iw_plus/rp_iw_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/siw/siw_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/siw_plus/siw_plus_planner.hxx;\
# ${PROJECT_SOURCE_DIR}/src/lapkt/planner/siw_plus-then-bfs_f/siw_plus_bfs_f.hxx"
# )