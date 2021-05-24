//
// Created by marhc on 19/05/2021.
//

#include "gtest/gtest.h"
#include "../Algorithms/Graph.h"
#include "../E-Stafetas/Company.h"


TEST(Interface, resolveOrders) {

    std::vector<Order*> orders;
    std::vector<Client*> clients;
    std::vector<Driver*> drivers;
    std::vector<Vehicle*> vehicles;
    Graph graph;

    graph.addNode(NodeInfo(10, 10), 1);
    graph.addNode(NodeInfo(10, 10), 2);
    graph.addNode(NodeInfo(10, 10), 3);
    graph.addNode(NodeInfo(10, 10), 4);
    graph.addNode(NodeInfo(10, 10), 5);
    graph.addNode(NodeInfo(10, 10), 6);

    clients.push_back(new Client("Burp"));
    clients.push_back(new Client("Berp"));

    Order* o1 = new Order();
    o1->tempClientId = 1;
    o1->tempDeliveryId = 1;
    o1->tempPickUpId = 2;

    Order* o2 = new Order();
    o2->tempClientId = 2;
    o2->tempDeliveryId = 3;
    o2->tempPickUpId = 4;

    Order* o3 = new Order();
    o3->tempPickUpId = 4;
    o3->tempDeliveryId = 5;
    o3->tempClientId = 2;

    orders.push_back(o1);
    orders.push_back(o2);
    orders.push_back(o3);

    Company company(drivers, clients, orders, vehicles, nullptr);

    ASSERT_NO_THROW(company.assignOrdersParameters(graph));

    for (const auto& order : company.getOrders()) {
        std::cout << *order << std::endl;
    }
}