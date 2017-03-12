cmake_minimum_required(VERSION 3.6)
project(skeleton_based_robot_reasoning)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(skeleton_based_robot_reasoning ${SOURCE_FILES} src/main.cpp)