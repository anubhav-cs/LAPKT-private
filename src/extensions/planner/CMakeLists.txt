target_sources(planner PRIVATE planner_py_module.cxx)
# target_link_libraries(planner PUBLIC planner)
if(MACOS_BUILD)
  set_target_properties(planner PROPERTIES
    INSTALL_RPATH "/usr/local/Frameworks/"
  )
else()
  set_target_properties(planner PROPERTIES
    INSTALL_RPATH "${CMAKE_INSTALL_RPATH}:$ORIGIN"
  )
endif()

# Planner configuration file in Python Package
install(
  FILES ${PROJECT_BINARY_DIR}/${REL_PYPI_LAPKT_ROOT}/planner/lapkt_planner_config.yml
  DESTINATION ${PYTHON_PKG_PATH}/site_package/lapkt/planner
  COMPONENT PYPACKAGE EXCLUDE_FROM_ALL
)