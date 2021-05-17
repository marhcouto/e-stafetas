//
// Created by marhc on 16/05/2021.
//

#include "Vehicle.h"

double Vehicle::maxRange = 1000000;

Vehicle::Vehicle(const std::string &licensePlate) : licensePlate(licensePlate) {
    this->range = Vehicle::maxRange;
};

std::string Vehicle::getLicensePlate() const {
    return licensePlate;
}

double Vehicle::getRange() const {
    return range;
}

double Vehicle::getMaxRange() const {
    return maxRange;
}

void Vehicle::setRange(double range) {
    this->range = range;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
    os << vehicle.licensePlate;
    return os;
}

std::istream& operator>>(std::istream& is, Vehicle& vehicle) {
    is >> vehicle.licensePlate;
    return is;
}

