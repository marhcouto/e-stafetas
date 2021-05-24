//
// Created by marhc on 24/05/2021.
//

#include "Menu.h"

Menu::Menu() {};

Menu::Menu(Graph graph, Company company) : graph(graph), company(company) {};

void Menu::loadingMenu() {

    std::cout << "LOADING MENU\n\n";

    std::cout << "To choose a option, type the number to which it is assigned\n";
    std::cout << "1- Load files with predefined garage\n";
    std::cout << "2- Load files without predefined garage\n";
    std::cout << "0- Quit\n";

    int option;
    Node* garage;
    while(true) {
        std::cout << "Option:\n";
        std::cin >> option;
        if (!std::cin.fail() && option <= 5 && option >= 0) break;
        std::cout << "Invalid answer\n";
    }
    switch (option) {
        case 1: {
            try {
                FileReader::readFileToGraph(graph, "porto_connected_edges.txt", "porto_connected_nodes.txt");
                FileReader::readTagsFile(graph, "recharge_points_porto.txt");
            } catch (FailedToOpenFileException& e) {
                std::cout << e.getMessage() << std::endl;
            } catch (NodeDoesNotExistException& e) {
                std::cout << e.getMessage() << std::endl;
            }
            garage = graph.findNode(3);
            break;
        }
        case 2: {
            try {
                FileReader::readFileToGraph(graph, "porto_final_edges.txt", "porto_final_nodes.txt");
                FileReader::readTagsFile(graph, "recharge_points_porto_nonconnected.txt");
            } catch (FailedToOpenFileException& e) {
                std::cout << e.getMessage() << std::endl;
            } catch (NodeDoesNotExistException& e) {
                std::cout << e.getMessage() << std::endl;
            }
            while(true) {
                int id;

                while(true) {
                    std::cout << "Garage ID:\n";
                    std::cin >> id;
                    if (!std::cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }
                garage = graph.findNode(id);
                if (garage != nullptr) {
                    garage->getInfo().setType(GARAGE);
                    graph.tarjan();
                    graph.eliminateInaccessible(id);
                    break;
                } else {
                    std::cout << "Node with said ID does not belong to the graph\n";
                }
            }
        }
        case 0: {
            return;
        }
    }
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
    this->company = Company(crew, clients, orders, fleet, garage);

    try {
        company.assignOrdersParameters(graph);
    } catch (ItemNotFoundException<int>& e) {
        std::cout << e.getMessage() << std::endl;
    } catch (NodeDoesNotExistException& e) {
        std::cout << e.getMessage() << std::endl;
    }
}

void Menu::startingMenu() {

    std::cout << "WELCOME TO E-STAFETAS\n\n";

    std::cout << "To choose a option, type the number to which it is assigned\n";
    std::cout << "1- E-STAFETAS info: clients, orders, drivers, etc.\n";
    std::cout << "2- Graph: add and remove nodes\n";
    std::cout << "3- Run route calculation\n";
    std::cout << "4- Edit current orders\n";
    std::cout << "5- View graph\n";
    std::cout << "0- Exit\n";

    while(true) {
        int option;
        while(true) {
            std::cout << "Option:\n";
            std::cin >> option;
            if (!std::cin.fail() && option <= 5 && option >= 0) break;
            std::cout << "Invalid answer\n";
        }
        switch (option) {
            case 1: {
                companyMenu();
                break;
            }
            case 2: {
                graphMenu();
                break;
            }
            case 3: {
                //Run_ROute
                break;
            }
            case 4: {
                orderMenu();
                break;
            }
            case 5: {
                GVMaker gv(graph);
                gv.display();
                break;
            }
            case 0: {
                return;
            }
        }
    }
    std::cout << "Goodbye\n";
}

void Menu::companyMenu() {
    std::cout << "E-STAFETAS Menu\n\n";
    std::cout << "To choose a option, type the number to which it is assigned\n";
    std::cout << "1- List all clients\n";
    std::cout << "2- List all past orders\n";
    std::cout << "3- List all drivers\n";
    std::cout << "4- List all vehicles\n";
    std::cout << "5- Find vehicle\n";
    std::cout << "6- Find client\n";
    std::cout << "7- Find order\n";
    std::cout << "8- Find driver\n";
    std::cout << "9- Add vehicle\n";
    std::cout << "10- Remove vehicle\n";
    std::cout << "11- Add client\n";
    std::cout << "12- Remove client\n";
    std::cout << "13- Add driver\n";
    std::cout << "14- Remove driver\n";
    std::cout << "15- List drivers by name\n";
    std::cout << "16- List clients by name\n";
    std::cout << "17- List past orders by client's name\n";
    std::cout << "0- Go back\n";

    bool stop = false;
    while(!stop) {
        int option;
        while(true) {
            std::cout << "Option:\n";
            std::cin >> option;
            if (!std::cin.fail() && option <= 17 && option >= 0) break;
            std::cout << "Invalid answer\n";
        }
        switch (option) {
            case 1: {
                //Print clients
                company.listClients();
                break;
            }
            case 2: {
                //Print all past orders
                company.listPastOrders();
                break;
            }
            case 3: {
                //List drivers
                company.listDrivers();
                break;
            }
            case 4: {
                //List vehicle
                company.listVehicles();
                break;

            }
            case 5: {
                //Find vehicle
                std::string licensePlate;
                std::cout << "What's the vehicle License Plate? \n";
                std::cin >> licensePlate;
                Vehicle* v = company.findVehicle(licensePlate);
                if( v == nullptr)
                    std::cout << "vehicle does not exist\n";
                else
                        v->print();

                break;
            }
            case 6: {
                //Find client
                int id;

                while (true) {
                    std::cout << "ID:\n";
                    std::cin >> id;
                    if (!std::cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }
                Client* c = company.findClient(id);
                if( c == nullptr)
                    std::cout << "Client does not exist\n";
                else
                    c->print();
                break;
            }
            case 7: {
                //Find order
                int id;
                while (true) {
                    std::cout << "ID:\n";
                    std::cin >> id;
                    if (!std::cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }
                Order* o = company.findOrder(id);
                if(o == nullptr)
                    std::cout << "Order does not exist\n";
                else
                    o->print();

                break;

            }
            case 8: {
                //Find driver
                int id;
                while (true) {
                    std::cout << "ID:\n";
                    std::cin >> id;
                    if (!std::cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }
                Driver* d = company.findDriver(id);
                if(d == nullptr)
                    std::cout << "Driver does not exist\n";
                else
                    d->print();

                break;
            }
            case 9: {
                //Add vehicle
                std::string licensePlate;

                std::cout << "License Plate:\n";
                std::cin >> licensePlate;

                if (!company.addVehicle(new Vehicle(licensePlate)))
                    std::cout << "Failed to add vehicle, it already exists\n";
                break;
            }
            case 10: {
                //remove vehicle
                std::string licensePlate;
                std::cout << "What's the vehicle License Plate? \n";
                std::cin >> licensePlate;
                if(!company.removeVehicle(licensePlate))
                    std::cout << "Failed to remove vehicle, wrong license plate \n";
                break;
            }
            case 11: {
                //Add client
                std::string name;

                std::cout << "Name:\n";
                std::cin >> name;

                company.addClient(new Client(name));
                break;
            }
            case 12: {
                //remove client
                int id;

                while(true) {
                    std::cout << "ID:\n";
                    std::cin >> id;
                    if (!std::cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }

                if(!company.removeClient(id))
                    std::cout << "Failed to remove client, id does not exist \n";

                break;
            }
            case 13: {
                //add driver
                std::string name;
                float salary;

                std::cout << "Name:\n";
                std::cin >> name;

                while(true) {
                    std::cout << "Salary:\n";
                    std::cin >> salary;
                    if (!cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }
                company.addDriver(new Driver(name, salary));
                break;
            }
            case 14: {
                //remove driver
                int id;

                while(true) {
                    std::cout << "ID:\n";
                    std::cin >> id;
                    if (!std::cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }
                if(!company.removeDriver(id))
                    std::cout << "Failed to remove driver, id does not exist\n";
                break;
            }
            case 15: {
                //List drivers by name
                    std::string name;
                    std::cout << "What's the driver's name?\n";
                    std::cin >> name;
                    company.listDriversName(name);

                    break;
            }
            case 16: {
                //List clients by name
                std::string name;
                std::cout << "What's the client's name?\n";
                std::cin >> name;
                company.listClientsName(name);

                break;
            }
            case 17: {
                //List orders by client
                int id;
                std::cout << "What's client id?\n";
                std::cin >> id;
                company.listOrdersClients(id);
                break;
            }
            case 0: {
                stop = true;
                break;
            }
            default: {

            }
        }
    }


}

void Menu::graphMenu() {

    std::cout << "To choose a option, type the number to which it is assigned\n";
    std::cout << "1- Add node\n";
    std::cout << "2- Add edge\n";
    std::cout << "0- Go back\n";

    bool stop = false;
    while(!stop) {
        int option;
        while(true) {
            std::cout << "Option:\n";
            std::cin >> option;
            if (!std::cin.fail() && option <= 2 && option >= 0) break;
            std::cout << "Invalid answer\n";
        }
        switch (option) {
            case 1: {
                int id;
                double latitude;
                double longitude;


            }
            case 2: {

            }
            case 0:{
                stop = true;
                return;
            }
            default: {

            }
        }
    }



}


void Menu::orderMenu() {

    std::cout << "To choose a option, type the number to which it is assigned\n";
    std::cout << "1- Add Order\n";
    std::cout << "2- Remove Order\n";
    std::cout << "3- List current orders\n";
    std::cout << "0- Go back\n";

    bool stop = false;
    while(!stop) {
        int option;
        while(true) {
            std::cout << "Option:\n";
            std::cin >> option;
            if (!std::cin.fail() && option <= 2 && option >= 0) break;
            std::cout << "Invalid answer\n";
        }
        switch (option) {
            case 1: {
                int n1, n2, c;
                std::string date;

                while(true) {
                    std::cout << "Pickup node ID:\n";
                    std::cin >> n1;
                    if (!cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }

                while(true) {
                    std::cout << "Delivery node ID:\n";
                    std::cin >> n2;
                    if (!cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }

                while(true) {
                    std::cout << "Client ID:\n";
                    std::cin >> c;
                    if (!cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }

                std::cout << "Date:\n";
                std::cin >> date;
                Node *node1, *node2;
                Client *client;

                try {
                    node1 = graph.findNode(n1);
                    node2 = graph.findNode(n2);
                    if (node1 == nullptr) throw NodeDoesNotExistException(n1, __func__, false);
                    if (node2 == nullptr) throw NodeDoesNotExistException(n2, __func__, false);
                } catch (NodeDoesNotExistException& e) {
                    std::cout << e.getMessage() << std::endl;
                }

                try {
                    client = company.findClient(c);
                    if (client == nullptr) throw ItemNotFoundException<int>("client", c, __func__);
                } catch (ItemNotFoundException<int>& e) {
                    std::cout << e.getMessage() << std::endl;
                }

                company.addOrder(new Order(node1, node2, client, date));
            }
            case 2: {
                int id;

                while(true) {
                    std::cout << "ID:\n";
                    std::cin >> id;
                    if (!cin.fail()) break;
                    std::cout << "Invalid answer\n";
                }

                if (!company.removeCurrentOrder(id))
                    std::cout << "Failed to remove order, id does not correspond to a currently active order\n";
                break;
            }
            case 3:{
                company.listCurrentOrders();
                break;
            }
            case 0: {
                stop = true;
                break;
            }
        }
    }

}

