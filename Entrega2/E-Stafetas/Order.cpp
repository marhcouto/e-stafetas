//
// Created by marhc on 16/05/2021.
//

#include "Order.h"

int Order::currentId = 1;

Order::Order() : Order(nullptr, nullptr) {};

Order::Order(Node* n1, Node* n2) : pickUp(n1), delivery(n2), orderId(Order::currentId), client(nullptr) {
    Order::currentId++;
}

int Order::getOrderId() const {
    return orderId;
}

Node* Order::getPickUp() const {
    return pickUp;
}

Node* Order::getDelivery() const {
    return delivery;
}

void Order::setPickUp(Node* pickUp) {
    this->pickUp = pickUp;
}

void Order::setDelivery(Node* delivery) {
    this->delivery = delivery;
}

Client *Order::getClient() const {
    return client;
}

void Order::setClient(Client *client) {
    Order::client = client;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << order.pickUp->getId() << " " << order.delivery->getId() << " " << order.client->getId();
    return os;
}

std::istream& operator>>(std::istream& is, Order& order) {
    int i1, i2, i3;
    is >> order.tempPickUpId >> order.tempDeliveryId >> order.tempClientId;
    return is;
}
