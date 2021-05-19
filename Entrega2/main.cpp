#include <iostream>
#include <iomanip>
#include "FileHandling/FileHandling.h"
#include "GVMaker.h"
#include "E-Stafetas/Company.h"

int main(int argc, char** argv) {

    std::cout << setprecision(10);
    std::cout << "!E-STAFETAS!" << std::endl;

    Graph graph;

    try {
        FileReader::readFileToGraph(graph, "porto_full_edges.txt", "porto_full_nodes_xy.txt");
    } catch (FailedToOpenFileException e) {
        std::cout << e.getMessage() << std::endl;
    } catch (UnexpectedEndOfFileException e) {
        std::cout << e.getMessage() << std::endl;
    }

    graphViewerMaker(graph);

    std::vector<Driver*> crew;
    std::vector<Order*> orders;
    std::vector<Vehicle*> fleet;
    std::vector<Client*> clients;

    try {
        FileReader::readFile<Client>(clients, "Clients.txt");
        FileReader::readFile<Vehicle>(fleet, "Vehicles.txt");
        FileReader::readFile<Driver>(crew, "Drivers.txt");
        FileReader::readFile<Order>(orders, "Orders.txt");
    } catch(FailedToOpenFileException e) {
        std::cout << e.getMessage() << std::endl;
    }

    Company company(crew, clients, orders, fleet);

    try {
        company.assignOrdersParameters(graph);
    } catch (ItemNotFoundException<int> e) {
        std::cout << e.getMessage() << std::endl;
    }



    return 0;
}
