add_executable(dz7_thread_sum thread_sum.c)
target_link_libraries(dz7_thread_sum PRIVATE pthread)

set_target_properties(dz7_thread_sum PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dz7"
)
