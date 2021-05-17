//
// Created by marhc on 16/05/2021.
//

#ifndef ENTREGA2_DRIVER_H
#define ENTREGA2_DRIVER_H

#include <iostream>
#include <string>

class Driver {
    std::string name;
    int age;
    int yearsExperience;
    float salary;
public:
    Driver(std::string name, int age, int exp, float salary);

    std::string getName() const;
    int getAge() const;
    int getYearsExperience() const;
    float getSalary() const;
    void setAge(int age);
    void setYearsExperience(int yearsExperience);
    void setSalary(float salary);

    friend std::ostream& operator<<(std::ostream& os, const Driver& driver);
    friend std::istream& operator>>(std::istream& is, Driver& driver);
};


#endif //ENTREGA2_DRIVER_H
