cmake_minimum_required(VERSION 3.25)
project(LearnOpenMP C)

set(CMAKE_C_STANDARD 11)

FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(hello_world examples/hello_world.c)
add_executable(vec_add examples/vec_add.c)
add_executable(coding examples/coding.c)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)