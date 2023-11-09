cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Graphs/AdjacencyMatrix.h Graphs/AdjacencyMatrix.cpp BranchAndBound/BranchAndBound.cpp BranchAndBound/BranchAndBound.h Tools/NodeBB.cpp Menu/Menu.cpp Tools/Timer.cpp Tools/Generator.cpp Tools/FileClass.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")

