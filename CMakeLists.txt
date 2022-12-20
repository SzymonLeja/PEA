cmake_minimum_required(VERSION 3.23)
project(pea)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(
        pea src/main.cpp

        inc/containers/AdjacencyMatrix.h
        src/containers/AdjacencyMatrix.cpp

        inc/containers/DynamicArray.hpp
        src/containers/DynamicArray.tpp

        inc/containers/Path.h
        src/containers/Path.cpp

        inc/utils/Enums.h

        inc/utils/Menu.h
        src/utils/Menu.cpp

        inc/utils/testing/Timer.h
        src/utils/testing/Timer.cpp

        inc/utils/FileManager.h
        src/utils/FileManager.cpp

        src/utils/RandomGenerator.cpp
        inc/utils/RandomGenerator.h

        inc/utils/testing/MatrixGenerator.h
        src/utils/testing/MatrixGenerator.cpp

        inc/utils/testing/TimeTests.h
        src/utils/testing/TimeTests.cpp

        inc/utils/testing/ErrorTests.h
        src/utils/testing/ErrorTests.cpp

        inc/algorithms/Algorithm.h

        inc/algorithms/BruteForce.h
        src/algorithms/BruteForce.cpp

        inc/algorithms/BranchAndBound.h
        src/algorithms/BranchAndBound.cpp

        inc/algorithms/DynamicProgramming.h
        src/algorithms/DynamicProgramming.cpp

        inc/algorithms/SimulatedAnnealing.h
        src/algorithms/SimulatedAnnealing.cpp
        inc/algorithms/TabuSearch.h
        src/algorithms/TabuSearch.cpp
        )