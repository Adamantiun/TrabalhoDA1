// ****************************************************************************************************
// ******************************************* CONTROLLER_H__ *****************************************
// ****************************************************************************************************

#ifndef PROJ1_CONTROLLER_H
#define PROJ1_CONTROLLER_H


#include "Truck.h"
#include "Order.h"
#include <vector>
#include <string>

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
    void readOrders();

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
    void addTruck(int volMax, int weightMax, int cost);

    void addOrder(int vol, int weight, int reward, int duration);



    // Removes
    /** @brief  Removes an Stop based on \p ID.*/
//    bool removeStop(string code);





    //Write
    /** @brief  Writes the .txt files upon Save&Quit*/
    void writeFiles();

    //Sets
    /** @brief  Set userName attribute.*/
    void setUsername(string username);

};

#endif //PROJ1_CONTROLLER_H
