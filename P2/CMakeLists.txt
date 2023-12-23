cmake_minimum_required(VERSION 3.24)
project(P2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(P2 main.cpp data_structures/Graph.cpp data_structures/Graph.h
        data_structures/MoveQueue.cpp data_structures/MoveQueue.h data_structures/Move.cpp
        data_structures/Move.h algorithms/TS.cpp algorithms/TS.h
        tests/AutoTests.cpp tests/AutoTests.h utils/Menu.cpp algorithms/Genetic.cpp algorithms/Genetic.h data_structures/Path.cpp data_structures/Path.h)