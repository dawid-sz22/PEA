cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Graphs/AdjacencyMatrix.h Graphs/AdjacencyMatrix.cpp Algorithms/BranchAndBound.cpp Algorithms/BranchAndBound.h Tools/NodeBB.cpp Menu/Menu.cpp Tools/Timer.cpp Tools/Generator.cpp Tools/FileClass.cpp Algorithms/BruteForce.cpp Algorithms/BruteForce.h Algorithms/BruteForce.h Algorithms/DynamicPrograming.cpp Algorithms/DynamicPrograming.h Metaheuristics/TabuSearch.cpp Metaheuristics/TabuSearch.h Tools/TabuElement.cpp Tools/TabuElement.h Metaheuristics/SimulatedAnnealing.cpp Metaheuristics/SimulatedAnnealing.h Metaheuristics/SimulatedAnnealing.h Metaheuristics/Genetic/GeneticAlgorithm.cpp Metaheuristics/Genetic/GeneticAlgorithm.h Metaheuristics/Genetic/Population.cpp Metaheuristics/Genetic/Population.h Metaheuristics/Genetic/Tour.cpp Metaheuristics/Genetic/Tour.h Metaheuristics/Genetic/Crossovers/CrossoverStrategy.h Metaheuristics/Genetic/Crossovers/PMXCrossover.cpp Metaheuristics/Genetic/Crossovers/PMXCrossover.h Metaheuristics/Genetic/Mutations/MutationStrategy.cpp Metaheuristics/Genetic/Mutations/MutationStrategy.h Metaheuristics/Genetic/Mutations/InsertMutation.cpp Metaheuristics/Genetic/Mutations/InsertMutation.h Metaheuristics/Genetic/Crossovers/OXCrossover.cpp Metaheuristics/Genetic/Crossovers/OXCrossover.h Metaheuristics/Genetic/Mutations/SwapMutation.cpp Metaheuristics/Genetic/Mutations/SwapMutation.h Metaheuristics/Genetic/Crossovers/CrossoverStrategy.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")

