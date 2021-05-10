//
// Created by marhc on 10/05/2021.
//

#ifndef ENTREGA2_UTILS_H
#define ENTREGA2_UTILS_H

#include <iostream>
#include "graphviewer.h"

typedef enum {RECHARGE, DELIVERY, PICKUP, NONE, GARAGE} interest;

class NodeInfo {
    const int nodeID;
    double latitude{};
    double longitude{};
    interest type;
public:
    NodeInfo(double latitude, double longitude, int nodeID) : latitude(latitude), longitude(longitude), nodeID(nodeID) {};
    explicit NodeInfo(int nodeID) : nodeID(nodeID) {};

    double getLatitude() const {
        return latitude;
    }
    void setLatitude(double latitude) {
        NodeInfo::latitude = latitude;
    }
    double getLongitude() const {
        return longitude;
    }
    void setLongitude(double longitude) {
        NodeInfo::longitude = longitude;
    }
    interest getType() const {
        return type;
    }
    void setType(interest type) {
        NodeInfo::type = type;
    }
    int getNodeID() const {
        return nodeID;
    }

    bool operator==(const NodeInfo& nodeInfo) const {
        return this->getNodeID() == nodeInfo.getNodeID();
    }
    friend std::ostream& operator<<(std::ostream& os, const NodeInfo& nodeInfo) {
        os << nodeInfo.getNodeID() << ":" << nodeInfo.getLatitude() << "-" << nodeInfo.getLongitude();
        return os;
    }
};


// To check the graph's state
void graphViewerMaker(Graph<NodeInfo> graph) {
    int counterID = 0;
    GraphViewer gv;

    gv.setCenter(sf::Vector2f(300, 300));

    for (Node<NodeInfo>* node : graph.getNodeSet())
        node->setVisited(false);

    for (Node<NodeInfo>* node : graph.getNodeSet()) {
        int id1, id2;
        id1 = node->getInfo().getNodeID();
        if (!node->getVisited()) {
            GraphViewer::Node& node1 = gv.addNode(node->getInfo().getNodeID(),
                                                  sf::Vector2f(node->getInfo().getLatitude(), node->getInfo().getLongitude()));
            node->setVisited(true);
        }
        for (Edge<NodeInfo>* edge : node->getAdj()) {
            id2 = edge->getDest()->getInfo().getNodeID();
            if (!edge->getDest()->getVisited()) {
                GraphViewer::Node &node2 = gv.addNode(edge->getDest()->getInfo().getNodeID(),
                                                      sf::Vector2f(edge->getDest()->getInfo().getLatitude(),
                                                                   edge->getDest()->getInfo().getLongitude()));
                edge->getDest()->setVisited(true);
            }
            gv.addEdge(counterID, gv.getNode(id1), gv.getNode(id2), GraphViewer::Edge::EdgeType::DIRECTED);
            counterID++;
        }
    }

    for (Node<NodeInfo>* node : graph.getNodeSet())
        node->setVisited(false);

    gv.createWindow();
    gv.join();
}


#endif //ENTREGA2_UTILS_H
