cmake_minimum_required(VERSION 3.22.1)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

add_executable(yadro src/main.cpp headers/tape.h headers/tape_impl.h src/tape_utils.cpp headers/tape_utils.h headers/tape_exception.h)
add_subdirectory(tests)
