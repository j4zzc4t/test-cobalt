cmake_minimum_required(VERSION 3.10)

# set the project name
project(test-cobalt)

# add the executable
add_executable(cobalt main.cxx)
add_library(comparator comparator.cxx)
target_link_libraries(cobalt PUBLIC comparator)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(cobalt PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}"
                          )