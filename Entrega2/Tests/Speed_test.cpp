//
// Created by marhc on 16/05/2021.
//

#include <chrono>
#include "TestsAux.h"
#include "gtest/gtest.h"

TEST(Speed_test, Shortest_Path_test) {
    /*Graph<NodeInfo> graph1;
    Graph<NodeInfo> graph2;

    ASSERT_NO_THROW(readFileToGraph(graph1, "edges_porto.txt", "nodes_x_y_porto.txt"));
    ASSERT_NO_THROW(readFileToGraph(graph2, "edges_porto.txt", "nodes_x_y_porto.txt"));

    graph1.assignIDM();
    graph2.assignIDM();

    auto time1 = std::chrono::high_resolution_clock::now();
    graph1.dijkstraMulti();
    auto time2 = std::chrono::high_resolution_clock::now();
    graph2.floydWarshallShortestPath();
    auto time3 = std::chrono::high_resolution_clock::now();

    std::cout << "Dijkstra's:" << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << std::endl;
    std::cout << "FloydWarshall's:" << std::chrono::duration_cast<std::chrono::microseconds>(time3 - time2).count() << std::endl;*/

}