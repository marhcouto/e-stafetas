//
// Created by marhc on 16/05/2021.
//

#ifndef ENTREGA2_ORDER_H
#define ENTREGA2_ORDER_H

#include <iostream>
#include "../Algorithms/Graph.h"
#include "../NodesInfo.h"

class Order {
    int orderId;
    Node<NodeInfo>* pickUp;
    Node<NodeInfo>* delivery;
public:
    int static currentId;

    Order() : Order(nullptr, nullptr) {};
    Order(Node<NodeInfo>* n1, Node<NodeInfo>* n2);

    int getOrderId() const;
    Node<NodeInfo> *getPickUp() const;
    Node<NodeInfo> *getDelivery() const;
    void setPickUp(Node<NodeInfo> *pickUp);
    void setDelivery(Node<NodeInfo> *delivery);

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};


#endif //ENTREGA2_ORDER_H
