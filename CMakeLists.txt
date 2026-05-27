cmake_minimum_required(VERSION 3.16)

project(acos_module4_homeworks C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Werror)
endif()

add_subdirectory(dz1)
add_subdirectory(dz2)
add_subdirectory(dz3)
add_subdirectory(dz4)
add_subdirectory(dz5)

