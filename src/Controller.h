// ****************************************************************************************************
// ******************************************* CONTROLLER_H__ *****************************************
// ****************************************************************************************************

#ifndef PROJ1_CONTROLLER_H
#define PROJ1_CONTROLLER_H


#include "Truck.h"
#include "Order.h"
#include <vector>
#include <string>
#include <set>
class Controller{
private:
    vector<Order> orderDB;
    vector<Truck> truckDB;
    string userName;

public:
    // Constructors
    /** @brief  Default constructor.*/
    Controller();
    /** @brief  Default destructor.*/
    ~Controller();

    // Gets


    /**
    * @brief Gets the truckDB of the Controller object.
    * @return the truckDB attribute.
    */
    vector<Truck>& getTrucks();

    /**
    * @brief Gets the userName of the Controller object.
    * @return the userName attribute.
    */
    string getUsername();

    /**
    * @brief Gets the orderDB of the Controller object.
    * @return the orderDB attribute.
    */
    vector<Order> getOrders();

    //Reads
    /**
    * @brief Reads orders1
     * */
    bool readOrders(int orderNo);

    /**
    * @brief Reads trucks
    * */
    void readTrucks();

    /**
    * @brief Reads userData
    * */
    bool readUserData();




    // Finds
//    /** @brief  Returns an Stop based on the \p code.*/
//    Stop& findStop(string code);
//
//    /** @brief  Returns an Line based on the \p code.*/
//    Line& findLine(string code);


    // Exists
//    /** @brief  Checks for the existence of an Stop based on \p code.*/
//    bool existsStop(string code);


    // Adds
    /** @brief  Adds a new Stop created with \p name, code, zone, latitude and longitude.*/
    void addTruck(int id, int volMax, int weightMax, int cost);

    void addOrder(int id, int vol, int weight, int reward, int duration);



    // Removes
    /** @brief  Removes an Stop based on \p ID.*/
//    bool removeStop(string code);





    //Write
    /** @brief  Writes the .txt files upon Save&Quit*/
    void writeFiles();

    //Sets
    /** @brief  Set userName attribute.*/
    void setUsername(string username);

    vector <Order> scenery3();

    vector<Truck> scenery1();

    vector<struct Truck> scenery2(int& getProfit);

    double deviation(int rank1, int rank2);

  //  int processTruck(Truck truck);

    int fu(int ind, int weight, int vol);

    int processTruck(Truck &truck);


    void processSelectedOrders(vector<vector<vector<int>>> &dp, Truck &truck);

    void sortTruckDBforS2();

    static bool compareCostBenefit(const Truck &t1, const Truck &t2);

    void clearOrders();
};

#endif //PROJ1_CONTROLLER_H
