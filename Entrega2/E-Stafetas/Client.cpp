//
// Created by marhc on 16/05/2021.
//

#include "Client.h"

int Client::currentId = 0;

Client::Client(std::string name) : name(std::move(name)) {
    id = Client::currentId;
    Client::currentId++;
}

std::string Client::getName() const {
    return name;
}

int Client::getId() const {
    return id;
}