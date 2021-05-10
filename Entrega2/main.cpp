#include <iostream>
#include "FileHandling.h"

int main() {
    std::cout << "!E-STAFETAS!" << std::endl;

    Graph<NodeInfo> graph;

    try {
        readFileToGraph(graph, "edges.txt", "nodes.txt");
    } catch (FailedToOpenFileException e) {
        std::cout << e.getMessage() << std::endl;
    } catch (UnexpectedEndOfFileException e) {
        std::cout << e.getMessage() << std::endl;
    }

    graphViewerMaker(graph);



    return 0;
}
