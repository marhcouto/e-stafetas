//
// Created by marhc on 17/05/2021.
//

#include "Company.h"

const vector<Driver> &Company::getCrew() const {
    return crew;
}

void Company::setCrew(const vector<Driver> &crew) {
    Company::crew = crew;
}

const vector<Order> &Company::getOrders() const {
    return orders;
}

void Company::setOrders(const vector<Order> &orders) {
    Company::orders = orders;
}

const vector<Vehicle> &Company::getFleet() const {
    return fleet;
}

void Company::setFleet(const vector<Vehicle> &fleet) {
    Company::fleet = fleet;
}

const vector<Client> &Company::getClients() const {
    return clients;
}

void Company::setClients(const vector<Client> &clients) {
    Company::clients = clients;
}
