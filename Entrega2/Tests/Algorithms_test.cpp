//
// Created by marhc on 11/05/2021.
//

#include "gtest/gtest.h"
#include "../Algorithms/Graph.h"

template <class T>
void checkSinglePath(std::vector<T> path, std::string expected) {
    std::stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++)
        ss << path[i] << " ";
    EXPECT_EQ(expected, ss.str());
}

TEST(Algorithms_test, Tarjan_test) {
    Graph<std::string> graph;

    graph.addNode("Baba", 1);
    graph.addNode("Baba", 2);
    graph.addNode("Baba", 3);
    graph.addNode("Baba", 4);
    graph.addNode("Baba", 5);
    graph.addNode("Baba", 6);

    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 1, 1);
    graph.addEdge(3, 6, 1);
    graph.addEdge(6, 2, 1);
    graph.addEdge(4, 5, 1);
    graph.addEdge(4, 6, 1);

    graph.tarjan();
    EXPECT_EQ(graph.findNode(1)->getLow(), graph.findNode(2)->getLow());
    EXPECT_EQ(graph.findNode(1)->getLow(), graph.findNode(3)->getLow());
    EXPECT_EQ(graph.findNode(3)->getLow(), graph.findNode(2)->getLow());
    EXPECT_EQ(graph.findNode(1)->getLow(), graph.findNode(6)->getLow());
    EXPECT_EQ(graph.findNode(6)->getLow(), graph.findNode(2)->getLow());
    EXPECT_FALSE(graph.findNode(4)->getLow() == graph.findNode(1)->getLow());
    EXPECT_FALSE(graph.findNode(4)->getLow() == graph.findNode(2)->getLow());
    EXPECT_FALSE(graph.findNode(5)->getLow() == graph.findNode(3)->getLow());
    EXPECT_FALSE(graph.findNode(5)->getLow() == graph.findNode(6)->getLow());

    EXPECT_NO_THROW(graph.eliminateInaccessible(1));
    EXPECT_EQ(graph.getNodeSet().size(), 4);
}

TEST(Algorithms_test, FloydWarshall_test) {
    Graph<std::string> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addNode("BEH", i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    myGraph.assignIDM();

    myGraph.floydWarshallShortestPath();
    checkSinglePath(myGraph.getShortestPath(1, 7), "1 2 4 5 7 ");
    checkSinglePath(myGraph.getShortestPath(5, 6), "5 7 6 ");
    checkSinglePath(myGraph.getShortestPath(7, 1), "7 6 4 3 1 ");
}

TEST(Alforithms_test, MultiDijkstras_test) {
    Graph<std::string> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addNode("BEH", i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    myGraph.assignIDM();

    myGraph.dijkstraMulti();
    checkSinglePath(myGraph.getShortestPath(1, 7), "1 2 4 5 7 ");
    checkSinglePath(myGraph.getShortestPath(5, 6), "5 7 6 ");
    checkSinglePath(myGraph.getShortestPath(7, 1), "7 6 4 3 1 ");
}

