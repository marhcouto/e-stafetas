//
// Created by marhc on 16/05/2021.
//

#include "Order.h"

int Order::currentId = 1;

Order::Order(Node<NodeInfo>* n1, Node<NodeInfo>* n2) : pickUp(n1), delivery(n2) {
    orderId = Order::currentId;
    Order::currentId++;
}

int Order::getOrderId() const {
    return orderId;
}

Node<NodeInfo>* Order::getPickUp() const {
    return pickUp;
}

Node<NodeInfo>* Order::getDelivery() const {
    return delivery;
}

void Order::setPickUp(Node<NodeInfo> *pickUp) {
    this->pickUp = pickUp;
}

void Order::setDelivery(Node<NodeInfo> *delivery) {
    this->delivery = delivery;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << order.orderId << order.pickUp->getId() << order.delivery->getId();
    return os;
}


