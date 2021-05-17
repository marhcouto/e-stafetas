//
// Created by marhc on 16/05/2021.
//

#include "FileHandling.h"


void FileReader::readFileToGraph(Graph& graph, std::string edgesFile, std::string nodesFile) {

    setprecision(8);

    int noNodes, noEdges;
    ifstream f;

    // Nodes
    f.open("../../GraphFiles/" + nodesFile, std::ifstream::in);
    if (f.fail()) throw FailedToOpenFileException(std::string("Error in ") + std::string(__func__) + std::string(": unable to open nodes file"));

    f >> noNodes;

    for (unsigned int i = 0; i < noNodes; i++) {
        if (f.eof()) throw UnexpectedEndOfFileException(std::string("Error in ") + std::string(__func__) + std::string(": unexpected enf of nodes file"));
        double latitude, longitude;
        int nodeID;
        std::string line;
        char uselessChar1, uselessChar2, uselessChar3, uselessChar4;
        f >> uselessChar1 >> nodeID  >> uselessChar2 >> latitude >> uselessChar3 >> longitude >> uselessChar4;
        graph.addNode(NodeInfo(latitude, longitude), nodeID);
    }
    f.close();

    // Edges
    f.open("../../GraphFiles/" + edgesFile, std::ifstream::in);
    if (f.fail()) throw FailedToOpenFileException(std::string("Error in ") + std::string(__func__) + std::string(": unable to open edges file"));

    f >> noEdges;

    for (unsigned int i = 0; i < noEdges; i++) {
        if (f.eof()) throw UnexpectedEndOfFileException(std::string("Error in ") + std::string(__func__) + std::string(": unexpected enf of edges file"));
        int nodeID1, nodeID2;
        char uselessChar;
        f >> uselessChar >> nodeID1 >> uselessChar >> nodeID2 >> uselessChar;
        Node* node1 = graph.findNode(nodeID1);
        Node* node2 = graph.findNode(nodeID2);
        graph.addEdge(node1, node2, NodeInfo::getDistance(node1->getInfo().getLatitude(), node1->getInfo().getLongitude(),
                                                          node2->getInfo().getLatitude(), node2->getInfo().getLongitude()));
    }
    f.close();
}

void FileReader::readOrders(Graph &graph, std::string file) {
    std::ifstream f;

    f.open("../../GraphFiles/" + file, std::ifstream::in);
    if (f.fail()) throw FailedToOpenFileException(std::string("Error in ") + std::string(__func__) + std::string(": unable to open orders file"));


}