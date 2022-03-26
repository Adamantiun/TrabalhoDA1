//
// Created by 35196 on 26/03/2022.
//

#include "Order.h"

Order::Order(){
    this->weight=0;
    this->duration=0;
    this->reward=0;
    this->vol=0;
}

Order::~Order(){
}

Order::Order(const int &vol, const int &weight, const int &reward, const int &duration){
    this->weight=vol;
    this->duration=weight;
    this->reward=reward;
    this->vol=duration;
}

const int &Order::getWeight() const {
    return weight;
}

const int &Order::getDuration() const {
    return duration;
}

const int &Order::getReward() const {
    return reward;
}

const int &Order::getVol() const {
    return vol;
}

void Order::setWeight(const int &weight) {
    this->weight=weight;
}

void Order::setDuration(const int &duration) {
    this->duration=duration;
}

void Order::setReward(const int &reward) {
    this->reward=reward;
}

void Order::setVol(const int &vol) {
    this->vol=vol;
}