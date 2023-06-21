cmake_minimum_required(VERSION 3.23)
project(MiniProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        MiniProject
        Main.cpp
        Individual.h
        Individual.cpp
        GeneticAlgorithm.cpp
        GeneticAlgorithm.h
        KnapsackProblem.cpp
        KnapsackProblem.h
        Problem.h
        )
