cmake_minimum_required(VERSION 3.24)
project(P1)

set(CMAKE_CXX_STANDARD 17)

add_executable(P1 main.cpp utils/Time.cpp utils/Time.h data_structures/Graph.cpp data_structures/Graph.h
        data_structures/Stack.cpp data_structures/Stack.h data_structures/StackNode.cpp
        data_structures/StackNode.h algorithms/BF.cpp algorithms/BF.h algorithms/BB.cpp
        algorithms/BB.h algorithms/DP.cpp algorithms/DP.h
        tests/AutoTests.cpp tests/AutoTests.h utils/Menu.cpp)
