//
// Created by marhc on 10/05/2021.
//

#ifndef ENTREGA2_FILEHANDLING_H
#define ENTREGA2_FILEHANDLING_H

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "../Algorithms/Graph.h"
#include "../NodesInfo.h"

class UnexpectedEndOfFileException {
    const std::string message;
public:
    explicit UnexpectedEndOfFileException(std::string message) : message(std::move(message)) {};

    std::string getMessage() const {
        return message;
    }
};

class FailedToOpenFileException {
    const std::string message;
public:
    explicit FailedToOpenFileException(std::string message) : message(std::move(message)) {};
    string getMessage() const {
        return message;
    }
};


class FileReader {
public:
    static void readFileToGraph(Graph<NodeInfo>& graph, std::string edgesFile, std::string nodesFile);
    static void readOrders(Graph<NodeInfo>& graph, std::string file);
};



#endif //ENTREGA2_FILEHANDLING_H
