cmake_minimum_required(VERSION 3.0)

#project name
project(atests)
enable_testing()

set(VER_MJR 0)
set(VER_MIN 1)

set(CMAKE_BIULD_TYPE Debug)

aux_source_directory(${PROJECT_SOURCE_DIR} ATEST_SOURCES)

add_executable(float_load nload_test.cpp)
target_link_libraries(float_load ${EXTRA_LIBS})

add_test(NAME float_load COMMAND float_load)

