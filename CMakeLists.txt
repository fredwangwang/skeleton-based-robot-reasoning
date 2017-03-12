cmake_minimum_required(VERSION 2.8)
project(skeleton_based_robot_reasoning)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/get_file_list.cpp src/get_file_list.h)
add_executable(skeleton_based_robot_reasoning ${SOURCE_FILES} src/main.cpp)

