//
// Created by 35196 on 26/03/2022.
//

#include "Truck.h"

Truck::Truck() {
    this->cost=0;
    this->volMax=0;
    this->weightMax=0;
}

Truck::Truck(const int &volMax, const int &weightMax, const int &cost) {
    this->cost=cost;
    this->volMax=volMax;
    this->weightMax=weightMax;
}

Truck::~Truck() {}

const int &Truck::getCost() const {
    return cost;
}

const int &Truck::getVolMax() const {
    return volMax;
}

const int &Truck::getWeightMax() const {
    return weightMax;
}

void Truck::setCost(const int &cost) {
    this->cost=cost;
}

void Truck::setVolMax(const int &volMax) {
    this->volMax=volMax;
}

void Truck::setWeightMax(const int &weightMax) {
    this->weightMax=weightMax;
}

