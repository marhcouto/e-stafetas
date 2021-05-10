cmake_minimum_required(VERSION 3.17)
project(Entrega2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Entrega2 main.cpp Algorithms/Graph.cpp Algorithms/Graph.h Algorithms/MutablePriorityQueue.h FileHandling.h NodeInfo.h)