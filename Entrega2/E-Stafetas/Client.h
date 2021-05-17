//
// Created by marhc on 16/05/2021.
//

#ifndef ENTREGA2_CLIENT_H
#define ENTREGA2_CLIENT_H

#include <string>
#include <utility>


class Client {
    std::string name;
    int id;
public:
    int static currentId;

    explicit Client(std::string name);

    std::string getName() const;
    int getId() const;
};


#endif //ENTREGA2_CLIENT_H
