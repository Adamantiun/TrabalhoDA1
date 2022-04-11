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
    for(auto i = 1;i<=6;i++){
        readOrders(i);
    }
    scenery1();
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
  //  orderDB.clear();
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


/*
int Controller::scenery1(){
    //FIRST FIT

    vector<Order> orderdb = orderDB;
    vector<Order> orderdbyVol = orderDB;
    vector<Truck> aux2 = truckDB;

    int n = orderdb.size();
    int j = 0;
    set<int> a;
    set<int> trucksIDS;
    for (int i = 0; i < n; i++) {
        // If this item can't f it in current bin
        if (orderdbyVol[i].getWeight() > aux2[j].getWeightMax() ||orderdbyVol[i].getVol() > aux2[j].getVolMax()  ) {
            j++;
        }
        else {
            a.insert(j);
            trucksIDS.insert(aux2[j].getId());
            aux2[j].setWeightMax(aux2[j].getWeightMax() - orderdbyVol[i].getWeight()); //mudo o tamanho
            aux2[j].setVolMax(aux2[j].getVolMax() - orderdbyVol[i].getVol()); //mudo o VOL
            j = 0;
        }
    }
    return a.size();

}
*/


int Controller::scenery1(){
    //FIRST FIT

    //*********************************************** ORDENACAO DAS ORDERS********************************************
    auto cmp = [] (Order order1, Order order2){ return order1.getWeight()>order2.getWeight();};
    auto cmpVol = [] (Order order1, Order order2){ return order1.getVol()>order2.getVol();};
    auto cmpID = []  (Order order1, Order order2){ return order1.getId()>order2.getId();};
    vector<Order> orderdb = orderDB;
    vector<Order> orderdbyVol = orderDB;
    //faço sort pelo peso
    sort(orderdb.begin(), orderdb.end(),cmp);
    //estabeleco uma especie de ranking pelo peso
    for(int i = 0; i<orderdb.size();i++){
        orderdb[i].setRankingWei(i);
    }
    //faço sort pelo volume
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
    auto cmpRak = []  (Order order1, Order order2){ return (order1.getRankingWei()+order1.getRankingVol())/2<
                                                           (order2.getRankingWei()+order2.getRankingVol())/2;};
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
    //sort both by id
    sort(truckbyVol.begin(),truckbyVol.end(),cmpTruckID);
    sort(aux2.begin(),aux2.end(),cmpTruckID);
    //put the wei in the vol vector
    for(int i = 0; i<truckbyVol.size();i++){
        truckbyVol[i].setRankingWei(aux2[i].getRankingWei());
    }
    auto cmpTruckRak = []  (Truck truck1, Truck truck2){ return (truck1.getRankingWei()+truck1.getRankingVol())/2<
                                                                (truck2.getRankingWei()+truck2.getRankingVol())/2;};
    //orderno pela media entre os dois
    sort(truckbyVol.begin(),truckbyVol.end(),cmpTruckRak);
    int n = orderdb.size();
    int j = 0;
    set<int> a;
    set<int> trucksIDS;
    for (int i = 0; i < n; i++) {
        // If this item can't f it in current bin
        if (orderdbyVol[i].getWeight() > truckbyVol[j].getWeightMax() ||orderdbyVol[i].getVol() > truckbyVol[j].getVolMax()  ) {
            j++;
        }
        else {
            a.insert(j);
            trucksIDS.insert(truckbyVol[j].getId());
            truckbyVol[j].setWeightMax(truckbyVol[j].getWeightMax() - orderdbyVol[i].getWeight()); //mudo o tamanho
            truckbyVol[j].setVolMax(truckbyVol[j].getVolMax() - orderdbyVol[i].getVol()); //mudo o VOL
            j = 0;
        }
    }
    return a.size();
}

/*
int Controller::scenery1(){
    //BEST FIT
    auto cmp = [] (Order order1, Order order2){ return order1.getWeight()<order2.getWeight();};
    auto cmpTruck = [] ( Truck truck1, Truck truck2 ) {return truck1.getWeightMax()<truck2.getWeightMax();};
    vector<Order> orderdb = orderDB;
    vector<Truck> aux2 = truckDB;

    int n = orderdb.size();
    int j = 0;
    set<int> a;
    int bin_rem = truckDB[0].getWeightMax();
    for (int i = 0; i < n; i++) {
        // If this item can't fit in current bin
        if (orderdb[i].getWeight() > aux2[j].getWeightMax() ||orderdb[i].getVol() > aux2[j].getVolMax()  ) {
            j++;
        }
        else {
            a.insert(j);
            aux2[j].setWeightMax(aux2[j].getWeightMax() - orderdb[i].getWeight()); //mudo o tamanho
            aux2[j].setVolMax(aux2[j].getVolMax() - orderdb[i].getVol()); //mudo o VOL
            j = 0;
        }
    }
    for (int i = 0; i < n; i++){
        // Find the best bin that can accomodate weight1[i]
        int j;
        // We have to initialize minimum space left and index of best bin
        // c is capacity
        int min = C + 1, bi = 0;
        for (j = 0; j < truckDB[j].getWeight(); j++){
            if (bin_rem[j] >= weight1[i] && bin_rem[j] - weight1[i] < min) {
                bi = j;
                min = bin_rem[j] - weight1[i];
            }

    return a.size();
}
*/
/*
int f(int ind, int weight, int vol, int *memo,vector<Order> Array){

    if(weight < 0 || vol < 0 ) return -INF;
    if(ind == Array.size()) return 0;
    int &ret= memo[ind,weight,vol];
    if(ret>0) return ret;
    int res = 0;
    for(int i=0;i<=75;i++)
        res = max(res, f(ind+1, weight-i*Array[ind].getWeight(), vol-i*Array[ind].getVol(),memo,Array));
    return ret = res;
}
int Controller::scenery1(){
    setMemo(memo);
    int memo[orderDB.size()][truckDB[0].getWeightMax()][truckDB[0].getVolMax()];
    int a = f(orderDB.size(),truckDB[0].getWeightMax(),truckDB[0].getVolMax(),memo,orderDB);
}
*/



