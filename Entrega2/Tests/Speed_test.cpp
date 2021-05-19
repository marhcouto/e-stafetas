//
// Created by marhc on 16/05/2021.
//

#include <chrono>
#include "gtest/gtest.h"
#include "../FileHandling/FileHandling.h"

TEST(Speed_test, Shortest_Path_test) {
    Graph graph1;
    Graph graph2;

    ASSERT_NO_THROW(FileReader::readFileToGraph(graph1, "edges.txt", "nodes.txt"));
    ASSERT_NO_THROW(FileReader::readFileToGraph(graph2, "edges.txt", "nodes.txt"));

    graph1.assignIDM();
    graph2.assignIDM();

    auto time1 = std::chrono::high_resolution_clock::now();
    graph1.dijkstraMulti();
    auto time2 = std::chrono::high_resolution_clock::now();
    graph2.floydWarshallShortestPath();
    auto time3 = std::chrono::high_resolution_clock::now();

    std::cout << "Dijkstra's:" << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << std::endl;
    std::cout << "FloydWarshall's:" << std::chrono::duration_cast<std::chrono::microseconds>(time3 - time2).count() << std::endl;

}

TEST(Speed_test, Connectivity_test) {
    Graph graph1;

    ASSERT_NO_THROW(FileReader::readFileToGraph(graph1, "porto_full_edges.txt", "porto_full_nodes_xy.txt"));

    graph1.assignIDM();
    auto time1 = std::chrono::high_resolution_clock::now();
    graph1.tarjan();
    ASSERT_NO_THROW(graph1.eliminateInaccessible(1));
    auto time2 = std::chrono::high_resolution_clock::now();

    std::cout << "Tarjan:" << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << std::endl;
}