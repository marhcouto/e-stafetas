//
// Created by marhc on 17/05/2021.
//

#include "Company.h"

Company::Company(std::vector<Driver*> d, std::vector<Client*> c, std::vector<Order*> o, std::vector<Vehicle*> v) : orders(o), crew(d), fleet(v), clients(c) {};

const std::vector<Driver*> &Company::getCrew() const {
    return crew;
}

void Company::setCrew(const vector<Driver*> &crew) {
    Company::crew = crew;
}

const std::vector<Order*> &Company::getOrders() const {
    return orders;
}

void Company::setOrders(const vector<Order*> &orders) {
    Company::orders = orders;
}

const std::vector<Vehicle*> &Company::getFleet() const {
    return fleet;
}

void Company::setFleet(const vector<Vehicle*> &fleet) {
    Company::fleet = fleet;
}

const std::vector<Client*> &Company::getClients() const {
    return clients;
}

void Company::setClients(const vector<Client*> &clients) {
    Company::clients = clients;
}

Client* Company::findClient(int id) {
    for (const auto& client : clients) {
        if (client->getId() == id)
            return client;
    }
    return nullptr;
}

Client* Company::findClient(std::string name) {
    for (const auto& client : clients) {
        if (client->getName() == name)
            return client;
    }
    return nullptr;
}

Vehicle* Company::findVehicle(std::string licensePlate) {
    for (const auto& vehicle : fleet) {
        if (vehicle->getLicensePlate() == licensePlate)
            return vehicle;
    }
    return nullptr;
}

Order* Company::findOrder(int id) {
    for (const auto& order : orders) {
        if (order->getOrderId() == id)
            return order;
    }
    return nullptr;
}

Driver* Company::findDriver(int id) {
    for (const auto& driver : crew) {
        if (driver->getId() == id)
            return driver;
    }
    return nullptr;
}

Driver* Company::findDriver (std::string name) {
    for (const auto& driver : crew) {
        if (driver->getName() == name)
            return driver;
    }
    return nullptr;
}

void Company::assignOrdersParameters(Graph graph) {
    for (Order* order : orders) {
        order->setPickUp(graph.findNode(order->tempPickUpId));
        order->setDelivery(graph.findNode(order->tempDeliveryId));
        Client* c = this->findClient(order->tempClientId);
        if (c == nullptr) throw ItemNotFoundException<int>("client", order->tempClientId, __func__);
        order->setClient(this->findClient(order->tempClientId));
    }
}
