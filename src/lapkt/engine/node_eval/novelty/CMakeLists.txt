target_sources(core
    PRIVATE
        node_novelty_spaces.hxx
        novelty.hxx
        approximate_novelty.hxx
        approximate_novelty_partition_1.hxx
        approximate_novelty_partition_2.hxx
        novelty_partition.hxx
        novelty_partition_1.hxx
        novelty_partition_2.hxx
)

install(
    FILES
        node_novelty_spaces.hxx
        novelty.hxx
        approximate_novelty.hxx
        approximate_novelty_partition_1.hxx
        approximate_novelty_partition_2.hxx
        novelty_partition.hxx
        novelty_partition_1.hxx
        novelty_partition_2.hxx
    DESTINATION
        ${CMAKE_INSTALL_PREFIX}/${REL_CORE_INC_DIR}/lapkt/engine/node_eval/novelty
    COMPONENT
        lapkt 
)