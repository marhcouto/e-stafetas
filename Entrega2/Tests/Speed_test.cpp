//
// Created by marhc on 16/05/2021.
//

#include <chrono>
#include "gtest/gtest.h"
#include "../FileHandling.h"

TEST(Speed_test, Shortest_Path_test) {
    Graph<NodeInfo> graph1;
    Graph<NodeInfo> graph2;

    ASSERT_NO_THROW(FileReader::readFileToGraph(graph1, "edges.txt", "nodes.txt"));
    ASSERT_NO_THROW(FileReader::readFileToGraph(graph2, "edges.txt", "nodes.txt"));

    graph1.assignIDM();
    graph2.assignIDM();

    for (Node<NodeInfo>* n : graph1.getNodeSet()) {
        for (Edge<NodeInfo>* e : n->getAdj()) {
            EXPECT_EQ(e->getWeight(), 37);
        }
    }

    auto time1 = std::chrono::high_resolution_clock::now();
    graph1.dijkstraMulti();
    auto time2 = std::chrono::high_resolution_clock::now();
    graph2.floydWarshallShortestPath();
    auto time3 = std::chrono::high_resolution_clock::now();

    std::cout << "Dijkstra's:" << std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() << std::endl;
    std::cout << "FloydWarshall's:" << std::chrono::duration_cast<std::chrono::microseconds>(time3 - time2).count() << std::endl;

}