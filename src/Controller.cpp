// ****************************************************************************************************
// ****************************************** CONTROLLER_CPP__ ****************************************
// ****************************************************************************************************

#include "Controller.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>


Controller::Controller() {
    readTrucks();
    readOrders();
}

void Controller::readTrucks() {
/*    ifstream stopsFile;
    stopsFile.open("../src/dataset/stops.csv");
    if (stopsFile.fail()) {
        cout << "This file doesn't exist!\n";
    } else {
        string line;
        stopsFile >> line;
        stopsFile.ignore();
        int index=0;
        while (!stopsFile.eof() && stopsFile.peek()!='\n') {
            Stop stop;
            stopsFile >> stop;
            stop.setIndex(index);
            this->stopDB.push_back(stop);
            index++;
        }
        stopDB.pop_back();
    }
    stopsFile.close();
    graph = Graph(stopDB.size(), true);
    for (int i=0;i<stopDB.size();i++){
        graph.addStop(stopDB.at(i));
    }

*/
}

void Controller::readOrders() {
    /*
    ifstream ordersFile;
    ordersFile.open("../src/Data/orders1.txt");
    if (ordersFile.fail()) {
        cout << "This file doesn't exist!\n";
    }
    else {
        string l;
        ordersFile >> l;
        linesFile.ignore();
        while (!linesFile.eof() && linesFile.peek() != '\n') {
            Line line;
            linesFile >> line;
            if(line.getCode().find('M') == string::npos)
                this->linesDB.push_back(line);
        }
        linesDB.pop_back();
        linesFile.close();
        extractStopsFromLines();
    }
     */
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
    return true;
     */
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



void Controller::addTruck(int volMax, int weightMax, int cost) {
    Truck truck = Truck(volMax,weightMax,cost);
    truckDB.push_back(truck);
}

void Controller::addOrder(int vol, int weight, int reward, int duration) {
    Order order = Order(vol,weight,reward,duration);
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






