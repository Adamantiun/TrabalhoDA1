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


    // Adds
    /** @brief  Adds a new Stop created with \p name, code, zone, latitude and longitude.*/
    void addTruck(int id, int volMax, int weightMax, int cost);

    void addOrder(int id, int vol, int weight, int reward, int duration);

    //Sceneries

    /** @brief  Processes scenery 1 and returns the trucks used.*/
    vector<Truck> scenery1();

    /** @brief  Processes scenery 2 and returns the trucks used,
     * also returns the profit through the parameter getProfit.*/
    vector<Truck> scenery2(int& getProfit);

    /** @brief  Processes scenery 3 and returns the orders to be shipped ordered,
     * also returns the average delivery time through the parameter getMeanTime*/
    vector <Order> scenery3(int& getMeanTime);



    double deviation(int rank1, int rank2);

    int processTruck(Truck &truck);


    void processSelectedOrders(vector<vector<vector<int>>> &dp, Truck &truck);

    void sortTruckDBforS2();

    static bool compareCostBenefit(const Truck &t1, const Truck &t2);

    void clearOrders();
};

#endif //PROJ1_CONTROLLER_H
