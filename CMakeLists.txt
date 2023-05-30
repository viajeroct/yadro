cmake_minimum_required(VERSION 3.22.1)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

add_executable(yadro main.cpp tape.h tape_impl.h tape_utils.cpp tape_utils.h)
add_subdirectory(tests)
