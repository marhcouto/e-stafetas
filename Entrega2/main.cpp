#include <iostream>
#include <iomanip>
#include "FileHandling/FileHandling.h"
#include "GVMaker.h"
#include "E-Stafetas/Company.h"


int main(int argc, char** argv) {


    std::cout << setprecision(10);
    //std::string edgesFile, nodesFile;

    std::cout << "!E-STAFETAS!" << std::endl;
    /*std::cout << "Edges file:" << std::endl;
    std::cin >> edgesFile;
    std::cout << "Nodes file:" << std::endl;
    std::cin >> nodesFile;*/

    Graph graph;

    try {
        FileReader::readFileToGraph(graph, "porto_full_edges.txt", "porto_full_nodes_xy.txt");
    } catch (FailedToOpenFileException e) {
        std::cout << e.getMessage() << std::endl;
    } catch (UnexpectedEndOfFileException e) {
        std::cout << e.getMessage() << std::endl;
    }

    graphViewerMaker(graph);


    return 0;
}
