//
// Created by marhc on 16/05/2021.
//

#include "Driver.h"


Driver::Driver(std::string name, int age, int exp, float salary) : name(std::move(name)), age(age), yearsExperience(exp), salary(salary) {}

std::string Driver::getName() const {
    return name;
}

int Driver::getAge() const {
    return age;
}

int Driver::getYearsExperience() const {
    return yearsExperience;
}

float Driver::getSalary() const {
    return salary;
}

void Driver::setAge(int age) {
    Driver::age = age;
}

void Driver::setYearsExperience(int yearsExperience) {
    Driver::yearsExperience = yearsExperience;
}

void Driver::setSalary(float salary) {
    Driver::salary = salary;
}

std::ostream& operator<<(std::ostream& os, const Driver& driver) {
    os << driver.name << driver.age << driver.yearsExperience << driver.salary;
    return os;
}

std::istream& operator>>(std::istream& is, Driver& driver) {
    is >> driver.name >> driver.age >> driver.yearsExperience >> driver.salary;
    return is;
}