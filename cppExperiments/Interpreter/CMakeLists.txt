cmake_minimum_required(VERSION 3.5)
project(Interpreter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp format.cc Interpreter.cpp)
add_executable(Interpreter ${SOURCE_FILES})