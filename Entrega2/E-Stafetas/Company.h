//
// Created by marhc on 17/05/2021.
//

#ifndef ENTREGA2_COMPANY_H
#define ENTREGA2_COMPANY_H

#include <sstream>

#include "Client.h"
#include "Order.h"
#include "Driver.h"
#include "Vehicle.h"
#include "../Algorithms/Graph.h"

template <class T>
class ItemNotFoundException {
    std::string message;
public:
    ItemNotFoundException(std::string type, T data, std::string funcName) {
        std::stringstream ss;
        ss << "Error in " << funcName << ": " << data << " " << type << " was not found";
        message = ss.str();
    }
    const string &getMessage() const {
        return message;
    }
};

class Company {
    std::vector<Driver*> crew;
    std::vector<Order*> orders;
    std::vector<Vehicle*> fleet;
    std::vector<Client*> clients;
public:
    Company(std::vector<Driver*> d, std::vector<Client*> c, std::vector<Order*> o, std::vector<Vehicle*> v);

    const vector<Driver*> &getCrew() const;
    void setCrew(const vector<Driver*> &crew);
    const vector<Order*> &getOrders() const;
    void setOrders(const vector<Order*> &orders);
    const vector<Vehicle*> &getFleet() const;
    void setFleet(const vector<Vehicle*> &fleet);
    const vector<Client*> &getClients() const;
    void setClients(const vector<Client*> &clients);

    Client* findClient(int id);
    Client* findClient(std::string name);
    Order* findOrder(int id);
    Vehicle* findVehicle(std::string licensePlate);
    Driver* findDriver(std::string name);
    Driver* findDriver(int id);


    void assignOrdersParameters(Graph graph);
};


#endif //ENTREGA2_COMPANY_H
