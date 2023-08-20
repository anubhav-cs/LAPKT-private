target_sources(core
  PRIVATE
    at_bfsf_planner.cxx
)

install(
  FILES
    at_bfsf_planner.hxx
  DESTINATION
    ${CMAKE_INSTALL_PREFIX}/${REL_CORE_INC_DIR}/lapkt/planner/at_bfs_f
  COMPONENT
    lapkt
)

cat(
  ${CMAKE_CURRENT_SOURCE_DIR}/planner_config.yml 
  ${PROJECT_BINARY_DIR}/${REL_PYPI_LAPKT_ROOT}/planner/lapkt_planner_config.yml
)
