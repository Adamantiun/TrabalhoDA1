// ****************************************************************************************************
// ****************************************** CONTROLLER_CPP__ ****************************************
// ****************************************************************************************************

#include "Controller.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>


Controller::Controller() {
    readTrucks();
}

void Controller::readTrucks() {
    ifstream trucksFile;
    trucksFile.open("../src/Data/trucks");
    if (trucksFile.fail()) {
        cout << "This file doesn't exist!\n";
    }
    else {
        string line;
        getline(trucksFile,line);
        while (!trucksFile.eof() && trucksFile.peek()!='\n') {
            Truck truck = Truck();
            getline(trucksFile,line, ' ');
            truck.setId(stoi(line));
            getline(trucksFile,line, ' ');
            truck.setVolMax(stoi(line));
            getline(trucksFile,line, ' ');
            truck.setWeightMax(stoi(line));
            getline(trucksFile,line);
            truck.setCost(stoi(line));
            truckDB.push_back(truck);
        }
        trucksFile.close();
    }
}

bool Controller::readOrders(int orderNo) {
    ifstream ordersFile;
    ordersFile.open("../src/Data/orders" + to_string(orderNo));
    if (ordersFile.fail()) {
        return false;
    }
    orderDB.clear();
    string line;
    getline(ordersFile,line);
    while (!ordersFile.eof() && ordersFile.peek()!='\n') {
        Order order = Order();
        getline(ordersFile,line, ' ');
        order.setId(stoi(line));
        getline(ordersFile,line, ' ');
        order.setVol(stoi(line));
        getline(ordersFile,line, ' ');
        order.setWeight(stoi(line));
        getline(ordersFile,line, ' ');
        order.setReward(stoi(line));
        getline(ordersFile,line);
        order.setDuration(stoi(line));
        orderDB.push_back(order);
    }
    ordersFile.close();
    return true;
}


bool Controller::readUserData() {
    /*
    ifstream userFile;
    userFile.open("../src/dataset/userData.txt");
    if (userFile.fail()) {
        return false;
    }
    char buf[256];
    userFile.getline(buf, 100, '\n');
    userName = buf;
    userFile.getline(buf, 100, '\n');
    walkingFactor = atoi(buf);
    userFile.getline(buf, 100, '\n');
    maxWalingDistance = atoi(buf);

    userFile.close();
     */
    return true;

}

Controller::~Controller(){
    truckDB.clear();
    orderDB.clear();
}

vector<Order> Controller::getOrders() {
    return orderDB;
}

vector<Truck>& Controller::getTrucks() {
    return truckDB;
}

/*
Stop& Controller::findStop(string code) {
    for(int i=0; i<stopDB.size(); i++)
        if(stopDB[i].getCode() == code)
            return stopDB[i];
    Stop* nill = new Stop();
    return *nill;
}

Line& Controller::findLine(string code) {
    for(auto& line :linesDB){
        if(line.getCode()==code)
            return line;
    }
    Line* nill=NULL;
    return *nill;
}


*/



void Controller::addTruck(int id,int volMax, int weightMax, int cost) {
    Truck truck = Truck(id, volMax,weightMax,cost);
    truckDB.push_back(truck);
}

void Controller::addOrder(int id, int vol, int weight, int reward, int duration) {
    Order order = Order(id, vol,weight,reward,duration);
    orderDB.push_back(order);
}

/*
bool Controller::removeStop(string code) {
    for(auto stop : stopDB);
    vector<Stop>::iterator it;
    for(it = stopDB.begin(); it<stopDB.end(); it++)
        if(it->getCode()==code){
            stopDB.erase(it);
            return true;
        }
    return false;
}
*/







string Controller::getUsername(){
    return userName;
}



void Controller::writeFiles() {
    ofstream userFile;
    userFile.open("../src/dataset/userData.txt");
    userFile << userName << "\n" ;
}

void Controller::setUsername(string username) {
    this->userName = username;
}


vector<Order> Controller::scenery3(){
    vector<Order> res;
    vector<Order> aux = orderDB;
    sort(aux.begin(),aux.end(), [](const Order &a, const Order &b) {
        return a.getDuration() < b.getDuration();});
    int total=0;
    int time=28800;
    for(int i=0; i<aux.size(); i++){
        if(total + aux[i].getDuration() >time){break;}
        total+=aux[i].getDuration();
        res.push_back(aux[i]);
    }
    return res;
}





