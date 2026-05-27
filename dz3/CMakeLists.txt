add_library(dz3_original_static STATIC fred.c john.c)
add_library(dz3_original_shared SHARED bill.c sam.c)
target_link_libraries(dz3_original_shared PRIVATE m)

add_library(dz3_preload SHARED interpose_preload.c)

add_executable(dz3_program main.c interpose_link.c)
target_link_libraries(dz3_program PRIVATE dz3_original_static dz3_original_shared m)

set_target_properties(dz3_original_shared dz3_preload PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dz3"
)
set_target_properties(dz3_program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dz3"
)

if(APPLE)
    target_link_options(dz3_program PRIVATE -Wl,-flat_namespace)
    set_target_properties(dz3_program PROPERTIES
        BUILD_RPATH "@loader_path"
        INSTALL_RPATH "@loader_path"
    )
else()
    set_target_properties(dz3_program PROPERTIES
        BUILD_RPATH "$ORIGIN"
        INSTALL_RPATH "$ORIGIN"
    )
endif()
