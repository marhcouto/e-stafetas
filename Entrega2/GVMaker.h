//
// Created by marhc on 13/05/2021.
//

#ifndef ENTREGA2_GVMAKER_H
#define ENTREGA2_GVMAKER_H

#include "graphviewer.h"
#include "Algorithms/Graph.h"
#include "sstream"

// To check the graph's state
void graphViewerMaker(Graph graph) {

    int counterID = 0;
    GraphViewer gv;

    gv.setCenter(sf::Vector2f(1000, 1000));

    for (Node* node : graph.getNodeSet())
        node->setVisited(false);

    for (Node* node : graph.getNodeSet()) {
        int id1, id2;
        id1 = node->getId();
        if (!node->getVisited()) {
            GraphViewer::Node& node1 = gv.addNode(node->getId(),sf::Vector2f((long) node->getInfo().getLatitude(), (long) node->getInfo().getLongitude()));
            node->setVisited(true);
        }
        for (Edge* edge : node->getAdj()) {
            id2 = edge->getDest()->getId();
            if (!edge->getDest()->getVisited()) {
                GraphViewer::Node &node2 = gv.addNode(edge->getDest()->getId(),sf::Vector2f(edge->getDest()->getInfo().getLatitude(),
                                                                   edge->getDest()->getInfo().getLongitude()));
                edge->getDest()->setVisited(true);
            }
            gv.addEdge(counterID, gv.getNode(id1), gv.getNode(id2), GraphViewer::Edge::EdgeType::DIRECTED);
            counterID++;
        }
    }

    for (Node* node : graph.getNodeSet())
        node->setVisited(false);

    gv.createWindow();
    gv.join();
}

#endif //ENTREGA2_GVMAKER_H
