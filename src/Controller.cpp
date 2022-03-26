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
    readStops();
    readLines();
}

void Controller::readStops(){
    ifstream stopsFile;
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
}

void Controller::readLines() {
    ifstream linesFile;
    linesFile.open("../src/dataset/lines.csv");
    if (linesFile.fail()) {
        cout << "This file doesn't exist!\n";
    }
    else {
        string l;
        linesFile >> l;
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
}



int Controller::getIndexStop(string code) {
    for(int i=0;i<=stopDB.size();i++){
        if(stopDB[i].getCode()==code){
            return i;
        }
    }
    return -1;
}

void Controller::extractStopsFromLines(){
    for(int i=0; i<linesDB.size(); i++){
        ifstream individLinesFile;
        string code = linesDB[i].getCode();
        individLinesFile.open("../src/dataset/line_" + code + "_0.csv");
        string prevStopCode, nextStopCode;
        getline(individLinesFile, prevStopCode);
        getline(individLinesFile, prevStopCode);
        int prevStop = getIndexStop(prevStopCode);
        while(getline(individLinesFile, nextStopCode)){
            int nextStop = getIndexStop(nextStopCode);
            double weight=haversine(graph.getStops()[prevStop].getLatitude(), graph.getStops()[prevStop].getLongitude(), graph.getStops()[nextStop].getLatitude(), graph.getStops()[nextStop].getLongitude());
            graph.addEdge(prevStop,nextStop,weight, code);
            linesDB.at(i).getL0().push_back(prevStop);
            prevStop=nextStop;
        }
        linesDB.at(i).getL0().push_back(prevStop);
        individLinesFile.close();
        individLinesFile.open("../src/dataset/line_" + code + "_1.csv");
        if(individLinesFile.peek()!='0') {
            getline(individLinesFile, prevStopCode);
            getline(individLinesFile, prevStopCode);
            prevStop = getIndexStop(prevStopCode);
            while(getline(individLinesFile, nextStopCode)){
                int nextStop = getIndexStop(nextStopCode);
                double weight= haversine(graph.getStops()[prevStop].getLatitude(), graph.getStops()[prevStop].getLongitude(), graph.getStops()[nextStop].getLatitude(), graph.getStops()[nextStop].getLongitude());
                graph.addEdge(prevStop,nextStop,weight, code);
                linesDB.at(i).getL1().push_back(prevStop);
                prevStop=nextStop;
            }
            linesDB.at(i).getL1().push_back(prevStop);
        }
        individLinesFile.close();
    }
}

void Controller::addEdgesInWalkingDistance() {
    double walkingDistance = (double) maxWalingDistance / 1000;
    for (int i = 0; i < graph.getStops().size()-1; i++) {
        for (int j = i+1; j < graph.getStops().size(); j++) {
            double weight = haversine(graph.getStops()[i].getLatitude(), graph.getStops()[i].getLongitude(),
                               graph.getStops()[j].getLatitude(), graph.getStops()[j].getLongitude());
            if (!graph.getStops()[i].isInAdj(graph.getStops()[j]) && weight <= walkingDistance) {
                graph.addEdge(i, j, weight * (3 + 2*(10-(double) walkingFactor)/10), "walking");
            }
            if (!graph.getStops()[j].isInAdj(graph.getStops()[i]) && weight <= walkingDistance) {
                graph.addEdge(j, i, weight, "walking");
            }
        }
    }
}

bool Controller::readUserData() {
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
}

Controller::~Controller(){
    stopDB.clear();
    linesDB.clear();
}

vector<Line> Controller::getLines() {
    return linesDB;
}

vector<Stop>& Controller::getStops() {
    return stopDB;
}


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



bool Controller::existsStop(string code) {
    for(auto& stop :stopDB){
        if(stop.getCode()==code)
            return true;
    }
    return false;
}



void Controller::addStop(string code, string name, string zone, float latitude, float longitude) {
    Stop stop = Stop(code,name,zone,latitude,longitude);
    stopDB.push_back(stop);
}


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



Stop Controller::getClosestStop(double lat1, double lon1) {
    Stop min = stopDB[0];
    for (int i=1;i<stopDB.size();i++){
        if (haversine(lat1,lon1,min.getLatitude(),min.getLongitude())> haversine(lat1,lon1,stopDB[i].getLatitude(),stopDB[i].getLongitude()))
            min = stopDB[i];
    }
    return min;
}

string Controller::getDirections(string origin, string destination, int type) {
    string directions = "";
    bool addFooter = false;
    if(origin.find(",") != string::npos){
        translateCoord(origin);
        directions+="Walk to nearest stop: " + graph.getStop(origin).getCode() + "\n";
    }
    if(destination.find(",") != string::npos){
        translateCoord(destination);
        addFooter = true;
    }
    vector<pair<int, string>> path;
    if(type == 0)
        path = graph.dijkstra_distance(graph.getStop(origin), graph.getStop(destination));
    else if(type == 1)
        path = graph.bfs(graph.getStop(origin), graph.getStop(destination));
    else
        path = graph.dijkstra_zones(graph.getStop(origin).getIndex(), graph.getStop(destination).getIndex());
    string line = path[1].second;
    directions += "From " + stopDB[path[0].first].getCode() + " by " + line + " to ";
    for (int i = 1; i < path.size(); ++i) {
        if(path[i].second!=line){
            line = path[i].second;
            directions += stopDB[path[i-1].first].getCode() + "\nFrom " + stopDB[path[i-1].first].getCode() + " by " + path[i].second +" to ";
        }
    }
    directions += graph.getStop(destination).getCode();
    if(addFooter)
        directions+="Then walk to destination";
    return directions;
}

void Controller::translateCoord(string& str){
    string lon = "";
    string lat = "";
    bool afterComma = false;
    for (int i = 0; i < str.size(); ++i) {
        if(str[i] == ','){
            afterComma = true;
            continue;
        }
        if(!afterComma)
            lat += str[i];
        else
            lon += str[i];
    }
    str = getClosestStop(stod(lat), stod(lon)).getCode();
}

vector<Stop> &Controller::getStopDB() {
    return this->stopDB;
}

string Controller::getUsername(){
    return userName;
}

 double Controller::haversine(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


void Controller::writeFiles() {
    ofstream userFile;
    userFile.open("../src/dataset/userData.txt");
    userFile << userName << "\n" << walkingFactor << "\n" << maxWalingDistance;
}

void Controller::setUsername(string username) {
    this->userName = username;
}

void Controller::setMaxWalkDist(int maxWD) {
    maxWalingDistance = maxWD;
}

void Controller::setWalkingFac(int walkF) {
    walkingFactor = walkF;
}

vector<int> Controller::getStopsNearCoords(double longitude, double latitude, double distance) {
    vector<int> res;
    cout << longitude << " " << latitude << " " << distance << endl;
    for (auto &&stop : stopDB)
        if(haversine(latitude, longitude, stop.getLatitude(), stop.getLongitude())<=distance)
            res.push_back(stop.getIndex());
    return res;
}




