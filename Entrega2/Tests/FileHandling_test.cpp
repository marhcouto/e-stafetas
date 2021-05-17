//
// Created by marhc on 13/05/2021.
//

#include "gtest/gtest.h"
#include "../FileHandling/FileHandling.h"

TEST(FileHandling_test, readingFromFile_test) {
    Graph graph;

    EXPECT_NO_THROW(FileReader::readFileToGraph(graph, "edges.txt", "nodes.txt"));
    EXPECT_EQ(graph.getNodeSet().size(), 289);
    EXPECT_EQ(graph.findNode(0)->getAdj().size(), 2);
    EXPECT_EQ(graph.findNode(1)->getAdj().size(), 2);
    EXPECT_EQ(graph.findNode(125)->getAdj().size(), 2);
    EXPECT_EQ(graph.findNode(286)->getAdj().size(), 1);
    EXPECT_EQ(graph.findNode(288)->getAdj().size(), 0);
    for (Node* n : graph.getNodeSet()) {
        for (Edge* e : n->getAdj()) {
            EXPECT_EQ(e->getWeight(), 37);
        }
    }

}
