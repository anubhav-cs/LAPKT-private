target_sources(core
    PRIVATE
    approximate_bfws.cxx
)

install(
  FILES
    approximate_bfws.hxx
  DESTINATION
    ${CMAKE_INSTALL_PREFIX}/${REL_CORE_INC_DIR}/lapkt/planner/apx_bfws
  COMPONENT
    lapkt
)

cat(${CMAKE_CURRENT_SOURCE_DIR}/planner_config.yml
    ${PROJECT_BINARY_DIR}/${REL_PYPI_LAPKT_ROOT}/planner/lapkt_planner_config.yml
)
