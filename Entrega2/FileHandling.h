//
// Created by marhc on 10/05/2021.
//

#ifndef ENTREGA2_FILEHANDLING_H
#define ENTREGA2_FILEHANDLING_H

#include <fstream>
#include <iostream>
#include <string>
#include "Algorithms/Graph.h"
#include "NodeInfo.h"

class UnexpectedEndOfFileException {
    const std::string message;
public:
    explicit UnexpectedEndOfFileException(std::string message) : message(std::move(message)) {};

    std::string getMessage() const {
        return message;
    }
};

class FailedToOpenFileException {
    std::string message;
public:
    explicit FailedToOpenFileException(std::string message) : message(std::move(message)) {};
    string getMessage() const {
        return message;
    }
};

void readFileToGraph(Graph<NodeInfo>& graph, std::string nodesFile, std::string edgesFile) {

    int noNodes, noEdges;
    ifstream f;

    // Nodes
    f.open("GraphFiles/" + nodesFile, std::ifstream::in);
    if (f.fail()) throw FailedToOpenFileException(std::string("Error in ") + std::string(__func__) + std::string(": unable to open nodes file"));

    f >> noNodes;

    for (unsigned int i = 0; i < noNodes; i++) {
        if (f.eof()) throw UnexpectedEndOfFileException(std::string("Error in ") + std::string(__func__) + std::string(": unexpected enf of nodes file"));
        double latitude, longitude;
        int nodeID;
        char uselessChar;
        f >> uselessChar >> nodeID  >> uselessChar >> latitude >> uselessChar >> longitude >> uselessChar;
        graph.addNode(NodeInfo(latitude, longitude, nodeID));
    }
    f.close();

    // Edges
    f.open("GraphFiles/" + edgesFile, std::ifstream::in);
    if (f.fail()) throw FailedToOpenFileException(std::string("Error in ") + std::string(__func__) + std::string(": unable to open edges file"));

    f >> noEdges;

    for (unsigned int i = 0; i < noEdges; i++) {
        if (f.eof()) throw UnexpectedEndOfFileException(std::string("Error in ") + std::string(__func__) + std::string(": unexpected enf of edges file"));
        int nodeID1, nodeID2;
        char uselessChar;
        f >> uselessChar >> nodeID1 >> uselessChar >> nodeID2 >> uselessChar;
        graph.addEdge(NodeInfo(nodeID1), NodeInfo(nodeID2), 1);
    }
    f.close();

}


#endif //ENTREGA2_FILEHANDLING_H
