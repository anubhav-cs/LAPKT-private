#----- Project Source -----#

add_subdirectory(planner)

add_subdirectory(wrapper)

# Translate PDDL input (leverages external libraries, including tarski)
add_subdirectory(pddl)