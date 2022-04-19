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
#include <xmath.h>
#include <functional>
#include <chrono>


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

void Controller::clearOrders(){
    orderDB.clear();
}


void Controller::addTruck(int id,int volMax, int weightMax, int cost) {
    Truck truck = Truck(id, volMax,weightMax,cost);
    truckDB.push_back(truck);
}

void Controller::addOrder(int id, int vol, int weight, int reward, int duration) {
    Order order = Order(id, vol,weight,reward,duration);
    orderDB.push_back(order);
}

vector<Order> Controller::scenery3(int& getMeanTime){
    vector<Order> res;
    vector<Order> aux = orderDB;
    sort(aux.begin(),aux.end(), [](const Order &a, const Order &b) {
        return a.getDuration() < b.getDuration();});
    int total=0;
    int time=28800;
    getMeanTime = 0;
    int i;
    for(i=0; i<aux.size(); i++){
        if(total + aux[i].getDuration() >time){break;}
        total+=aux[i].getDuration();
        getMeanTime += total;
        res.push_back(aux[i]);
    }
    getMeanTime/=i;
    return res;
}


double Controller::deviation(int rank1,int rank2){
    if((rank1 + rank2) == 0 ) return 1;
    double media = (rank1+rank2)/2.0;
    double deviation = 0;
    deviation += pow(rank1 - media, 2);
    deviation += pow(rank2 - media, 2);
    return deviation;
}
vector<Truck> Controller::scenery1(){
    //FIRST FIT

    //*********************************************** ORDENACAO DAS ORDERS********************************************
    auto cmp = [] (Order order1, Order order2){ return order1.getWeight()>order2.getWeight();};
    auto cmpVol = [] (Order order1, Order order2){return order1.getVol()>order2.getVol();};
    auto cmpID = []  (Order order1, Order order2){ return order1.getId()>order2.getId();};
    vector<Order> orderdb = orderDB;
    vector<Order> orderdbyVol = orderDB;
    //faço sort pelo peso
    sort(orderdb.begin(), orderdb.end(),cmp);
    //estabeleco uma especie de ranking pelo peso
    for(int i = 0; i<orderdb.size();i++){
        orderdb[i].setRankingWei(i);
    }
    //faco sort pelo volume
    sort(orderdbyVol.begin(),orderdbyVol.end(),cmpVol);
    //estabeleco uma especie de ranking pelo volume
    for(int i = 0; i<orderdbyVol.size();i++){
        orderdbyVol[i].setRankingVol(i);
    }
    //sort both by id
    sort(orderdb.begin(),orderdb.end(),cmpID);
    sort(orderdbyVol.begin(),orderdbyVol.end(),cmpID);
    //put the wei in the vol vector
    for(int i = 0; i<orderdbyVol.size();i++){
        orderdbyVol[i].setRankingWei(orderdb[i].getRankingWei());
    }
    auto cmpRak = [this]  (Order order1, Order order2){ if((order1.getRankingWei()+order1.getRankingVol())/2.0==(order2.getRankingWei()+order2.getRankingVol())/2.0)return deviation(order1.getRankingWei(),order1.getRankingVol()) < deviation(order2.getRankingWei(),order2.getRankingVol());
    else return (order1.getRankingWei()+order1.getRankingVol())/2.0<(order2.getRankingWei()+order2.getRankingVol())/2.0 ;};
    //orderno pela media entre os dois
    sort(orderdbyVol.begin(),orderdbyVol.end(),cmpRak);
    //ordeno o vector dos caminhoes, teoricamente tem que seguir uma abordagem semelhante, mas ainda nao foi implementada
    //***************************************************ORDERNACAO DOS TRUCKS********************************************************
    auto cmpTruck = [] ( Truck truck1, Truck truck2 ) {return truck1.getWeightMax()>truck2.getWeightMax();};
    auto cmpTruck_ByVol = [] ( Truck truck1, Truck truck2 ) {return truck1.getVolMax()>truck2.getVolMax();};
    auto cmpTruckID = []  (Truck truck1, Truck truck2){return truck1.getId()>truck2.getId();};
    vector<Truck> aux2 = truckDB;
    vector<Truck> truckbyVol = truckDB;
    sort(aux2.begin(), aux2.end(),cmpTruck);
    //estabeleco uma especie de ranking pelo peso
    for(int i = 0; i<aux2.size();i++){
        aux2[i].setRankingWei(i);
    }
    //faco sort pelo volume
    sort(truckbyVol.begin(),truckbyVol.end(),cmpTruck_ByVol);
    //estabeleco uma especie de ranking pelo volume
    for(int i = 0; i<truckbyVol.size();i++){
        truckbyVol[i].setRankingVol(i);
    }
    auto vec2 = truckbyVol;
    auto vec3 = aux2;
    //sort both by id
    sort(truckbyVol.begin(),truckbyVol.end(),cmpTruckID);
    sort(aux2.begin(),aux2.end(),cmpTruckID);
    //put the wei in the vol vector
    for(int i = 0; i<truckbyVol.size();i++){
        truckbyVol[i].setRankingWei(aux2[i].getRankingWei());
    }
    auto cmpTruckRak = [this]  (Truck truck1, Truck truck2){
        if((truck1.getRankingWei()+truck1.getRankingVol())/2.0==(truck2.getRankingWei()+truck2.getRankingVol())/2.0)return deviation(truck1.getRankingWei(),truck1.getRankingVol()) < deviation(truck2.getRankingWei(),truck2.getRankingVol());
        else return (truck1.getRankingWei()+truck1.getRankingVol())/2.0<(truck2.getRankingWei()+truck2.getRankingVol())/2.0 ;};
    //orderno pela media entre os dois
    sort(truckbyVol.begin(),truckbyVol.end(),cmpTruckRak);
    int n = orderdb.size();
    int j = 0;
    set<int> a;
    set<int> trucksIDS;
    vector<Truck> trucksUsed;
    for (int i = 0; i < n; i++) {
        if(orderdbyVol[i].getWeight()>vec3[0].getWeightMax() || orderdbyVol[i].getVol()> vec2[0].getVolMax()){
            continue;
        }
        // If this item can't f it in current bin
        if (orderdbyVol[i].getWeight() > truckbyVol[j].getWeightMax() ||orderdbyVol[i].getVol() > truckbyVol[j].getVolMax()  ) {
            j++;
            i--;
        }
        else {
            a.insert(j);
            trucksIDS.insert(truckbyVol[j].getId());
            truckbyVol[j].setWeightMax(truckbyVol[j].getWeightMax() - orderdbyVol[i].getWeight()); //mudo o tamanho
            truckbyVol[j].setVolMax(truckbyVol[j].getVolMax() - orderdbyVol[i].getVol()); //mudo o VOL
            truckbyVol[j].addOrder(orderdbyVol[i]);
            j = 0;
        }
    }
    for(auto x:a){
        trucksUsed.push_back(truckbyVol[x]);
    }
    return trucksUsed;
}


int Controller::processTruck(Truck &truck){
    if (truck.getVolMax() <= 0 || truck.getWeightMax()<=0) {
        return 0;
    }
    int n = orderDB.size();
    // we have 2 capacities, one of weight and other of volume
    vector<vector<vector<int>>>dp(n, vector<vector<int>>(truck.getWeightMax() + 1,vector<int>(truck.getVolMax()+1)));

    for (int i = 0; i < n; i++) {
        dp[i][0][0] = 0;
    }
    // if we have only one weight, we will take it if it is not more than the capacity
    for (int c = 0; c <= truck.getWeightMax(); c++) {
        for(int j= 0; j<= truck.getVolMax();j++){
            if (orderDB[0].getWeight() <= c && orderDB[0].getVol() <= j) {
                dp[0][c][j] = orderDB[0].getReward();
            }
        }
    }
    // process all sub-arrays for all the capacities
    for (int i = 1; i < n; i++) {
        for (int c = 1; c <= truck.getWeightMax() ; c++) {
            for(int j = 1; j <= truck.getVolMax(); j++){
                int profit1 = 0, profit2 = 0;
                // include the item, if it is not more than the capacity
                if (orderDB[i].getWeight() <= c && orderDB[i].getVol()<=j) {
                    profit1 = orderDB[i].getReward() + dp[i - 1][c - orderDB[i].getWeight()][j - orderDB[i].getVol()];
                }
                // exclude the item
                profit2 = dp[i - 1][c][j];
                // take maximum
                dp[i][c][j] = max(profit1, profit2);
            }
        }
    }
    int totalProfit = dp[orderDB.size() - 1][truck.getWeightMax()][truck.getVolMax()];
    processSelectedOrders(dp, truck);
    return totalProfit;

}
void Controller::processSelectedOrders(vector<vector<vector<int>>> &dp, Truck &truck) {
    ///This function processes the orders to be added to the truck and taken for the orders DB
    int totalProfit = dp[orderDB.size() - 1][truck.getWeightMax()][truck.getVolMax()];

    for (int i = orderDB.size() - 1; i > 0; i--) {
        if (totalProfit != dp[i - 1][ truck.getWeightMax()][truck.getVolMax()]) {
            //cout << " " << orderDB[i].getWeight()<<" || "<<orderDB[i].getVol();
            truck.addOrder(orderDB[i]);
            truck.setWeightMax(truck.getWeightMax()- orderDB[i].getWeight());
            truck.setVolMax(truck.getVolMax()- orderDB[i].getVol());
            totalProfit -= orderDB[i].getReward();
            orderDB.erase(orderDB.begin()+i);
            i++;
        }
    }



    if (totalProfit != 0) {
        truckDB[0].addOrder(orderDB[0]);
        orderDB.erase(orderDB.begin());
    }
}

void Controller :: sortTruckDBforS2(){
    sort(truckDB.begin(), truckDB.end(), compareCostBenefit);
}

bool Controller::compareCostBenefit(const Truck &t1, const Truck &t2) {
    return (t1.getWeightMax()*t1.getVolMax()/t1.getCost()) < (t2.getWeightMax()*t2.getVolMax()/t2.getCost());
}

vector<Truck> Controller::scenery2(int& getProfit){
    //chrono::steady_clock sc;
    //auto start = sc.now();

    sortTruckDBforS2(); //sort based on volume*weight/cost

    int total = 0; //profit counter

    vector<Truck> usedTrucks; //used trucks, returned for interface processing

    int i = 0; //current truck index

    while(!orderDB.empty() && i<truckDB.size()) {
        int reward = processTruck(truckDB[i]);

        if (reward == 0) { //no reward: skip truck
            i++;
            continue;
        }
        int cost = truckDB[i].getCost();
        int profit = reward - cost;

        if (profit <= 0) { //negative profit: return all orders and go to next truck
            for(auto order : truckDB[i].getOrdersInside())
                orderDB.push_back(order);
            truckDB[i].emptyTruck();
            continue;
        }
        total += profit;
        usedTrucks.push_back(truckDB[i]);
        i++;
    }
    getProfit = total; // setting given int as Total profit to be shown to user

    //auto end = sc.now();

    //auto time_span = static_cast<chrono::duration<double>>(end - start);
    //cout<<"Operation took: "<<time_span.count()<<" seconds !!!\n";
    return usedTrucks;
}

void Controller::clearTrucks() {
    for(auto &t: truckDB)
        t.emptyTruck();
}





