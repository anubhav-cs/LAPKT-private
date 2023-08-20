#----- Project Source -----#

# Search engines 
add_subdirectory(engine)

# Blueprints for strips model
add_subdirectory(model)

# lapkt template library(ltl) a set of utility blueprints
add_subdirectory(utils)

# Planners which leverage engine(s) in some particular configuration
add_subdirectory(planner)
