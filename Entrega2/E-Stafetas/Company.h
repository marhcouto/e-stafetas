//
// Created by marhc on 17/05/2021.
//

#ifndef ENTREGA2_COMPANY_H
#define ENTREGA2_COMPANY_H

#include "Client.h"
#include "Order.h"
#include "Driver.h"
#include "Vehicle.h"


class Company {
    std::vector<Driver> crew;
    std::vector<Order> orders;
    std::vector<Vehicle> fleet;
    std::vector<Client> clients;
public:
    const vector<Driver> &getCrew() const;

    void setCrew(const vector<Driver> &crew);

    const vector<Order> &getOrders() const;

    void setOrders(const vector<Order> &orders);

    const vector<Vehicle> &getFleet() const;

    void setFleet(const vector<Vehicle> &fleet);

    const vector<Client> &getClients() const;

    void setClients(const vector<Client> &clients);
};


#endif //ENTREGA2_COMPANY_H
