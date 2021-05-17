//
// Created by marhc on 16/05/2021.
//

#ifndef ENTREGA2_ORDER_H
#define ENTREGA2_ORDER_H

#include <iostream>
#include "../Algorithms/Graph.h"
#include "../Algorithms/NodesInfo.h"

class Order {
    int orderId;
    Node* pickUp;
    Node* delivery;
public:
    int static currentId;

    Order() : Order(nullptr, nullptr) {};
    Order(Node* n1, Node* n2);

    int getOrderId() const;
    Node* getPickUp() const;
    Node* getDelivery() const;
    void setPickUp(Node *pickUp);
    void setDelivery(Node *delivery);

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};


#endif //ENTREGA2_ORDER_H
