#include <iostream>
#include "FileHandling.h"
#include "gtest/gtest.h"

int main(int argc, char** argv) {

    // Tests
    std::cout << "Running all tests..." << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    /*std::cout << "!E-STAFETAS!" << std::endl;

    Graph<NodeInfo> graph;

    try {
        readFileToGraph(graph, "edges.txt", "nodes.txt");
    } catch (FailedToOpenFileException e) {
        std::cout << e.getMessage() << std::endl;
    } catch (UnexpectedEndOfFileException e) {
        std::cout << e.getMessage() << std::endl;
    }

    graphViewerMaker(graph);



    return 0;*/
}
