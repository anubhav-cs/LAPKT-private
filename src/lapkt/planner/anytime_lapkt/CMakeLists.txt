target_sources(core
  PRIVATE
    anytime_lapkt.cxx
)

install(
  FILES
    anytime_lapkt.hxx
  DESTINATION
    ${CMAKE_INSTALL_PREFIX}/${REL_CORE_INC_DIR}/lapkt/planner/anytime_lapkt
  COMPONENT
    lapkt
)

cat(
  ${CMAKE_CURRENT_SOURCE_DIR}/planner_config.yml 
  ${PROJECT_BINARY_DIR}/${REL_PYPI_LAPKT_ROOT}/planner/lapkt_planner_config.yml
)
