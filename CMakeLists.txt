cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Graphs/AdjacencyMatrix.h Graphs/AdjacencyMatrix.cpp Algorithms/BranchAndBound.cpp Algorithms/BranchAndBound.h Tools/NodeBB.cpp Menu/Menu.cpp Tools/Timer.cpp Tools/Generator.cpp Tools/FileClass.cpp Algorithms/BruteForce.cpp Algorithms/BruteForce.h Algorithms/BruteForce.h Algorithms/DynamicPrograming.cpp Algorithms/DynamicPrograming.h Metaheuristics/TabuSearch.cpp Metaheuristics/TabuSearch.h Tools/TabuElement.cpp Tools/TabuElement.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")

