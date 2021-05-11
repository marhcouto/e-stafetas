//
// Created by marhc on 11/05/2021.
//

#include "gtest/gtest.h"
#include "../Algorithms/Graph.h"

TEST(Algorithms_test, Tarjan_test) {
    /*Graph<int> graph;

    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(5);
    graph.addNode(6);

    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 1, 1);
    graph.addEdge(3, 6, 1);
    graph.addEdge(6, 2, 1);
    graph.addEdge(4, 5, 1);
    graph.addEdge(4, 6, 1);*/

    /*EXPECT_EQ(graph.findNode(1)->getLow(), graph.findNode(2)->getLow());
    EXPECT_EQ(graph.findNode(1)->getLow(), graph.findNode(3)->getLow());
    EXPECT_EQ(graph.findNode(3)->getLow(), graph.findNode(2)->getLow());
    EXPECT_EQ(graph.findNode(1)->getLow(), graph.findNode(6)->getLow());
    EXPECT_EQ(graph.findNode(6)->getLow(), graph.findNode(2)->getLow());
    EXPECT_FALSE(graph.findNode(4)->getLow() == graph.findNode(1)->getLow());
    EXPECT_FALSE(graph.findNode(4)->getLow() == graph.findNode(2)->getLow());
    EXPECT_FALSE(graph.findNode(5)->getLow() == graph.findNode(3)->getLow());
    EXPECT_FALSE(graph.findNode(5)->getLow() == graph.findNode(6)->getLow());*/
}