cmake_minimum_required(VERSION 3.9)
project(SFML_Manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system")

set(SOURCE_FILES main.cpp Object.cpp Object.h util.h util.cpp SFML_engine.cpp SFML_engine.h)
add_executable(SFML_Manager ${SOURCE_FILES})