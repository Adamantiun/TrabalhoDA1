// ****************************************************************************************************
// ******************************************* CONTROLLER_H__ *****************************************
// ****************************************************************************************************

#ifndef PROJ1_CONTROLLER_H
#define PROJ1_CONTROLLER_H


#include "Line.h"
#include "Graph.h"
#include <vector>
#include <string>

class Controller{
private:
    vector<Stop> stopDB;
    vector<Line> linesDB;
    Graph graph;
    string userName;
    int maxWalingDistance=10000;
    int walkingFactor;
public:
    // Constructors
    /** @brief  Default constructor.*/
    Controller();
    /** @brief  Default destructor.*/
    ~Controller();

    // Gets

    /**
    * @brief Gets the Graph of the Controller object.
    * @return the graph attribute.
    */
    Graph& getGraph() {return graph;}


    /**
    * @brief Gets the stopDB of the Controller object.
    * @return the stopDB attribute.
    */
    vector<Stop>& getStops();

    /**
    * @brief Gets the userName of the Controller object.
    * @return the userName attribute.
    */
    string getUsername();

    /**
    * @brief Gets the linesDB of the Controller object.
    * @return the linesDB attribute.
    */
    vector<Line> getLines();

    /**
    * @brief Gets the index of a Stop in the vector of the Controller object.
    * @return the index of the Stop
    */
    int getIndexStop(string code);

    /**
    * @brief Gets the stopDB of the Controller object.
    * @return the stopDB attribute.
    */
    vector<Stop>& getStopDB();

    /**
    * @brief Gets the directions from the origin to the destination.
    */
    string getDirections(string origin, string destination, int type = 0);

    /**
    * @brief Gets the Stops that are near from a location.
    */
    vector<int> getStopsNearCoords(double longitude, double latitude, double distance);

    //Reads
    /**
    * @brief Reads stops
     * */
    void readStops();

    /**
    * @brief Reads lines
    * */
    void readLines();

    /**
    * @brief Reads userData
    * */
    bool readUserData();

    /**
    * @brief Reads files from each line
    * */
    void extractStopsFromLines();



    // Finds
    /** @brief  Returns an Stop based on the \p code.*/
    Stop& findStop(string code);

    /** @brief  Returns an Line based on the \p code.*/
    Line& findLine(string code);


    // Exists
    /** @brief  Checks for the existence of an Stop based on \p code.*/
    bool existsStop(string code);


    // Adds
    /** @brief  Adds a new Stop created with \p name, code, zone, latitude and longitude.*/
    void addStop(string code, string name, string zone, float latitude, float longitude);

    /** @brief  Adds the edges that represent every change of line.*/
    void addEdgesInWalkingDistance();

    // Removes
    /** @brief  Removes an Stop based on \p ID.*/
    bool removeStop(string code);


    // Specified Gets
    /** @brief  Returns the closest stop from a location.*/
    Stop getClosestStop(double lat1, double lon1);


    //Write
    /** @brief  Writes the .txt files upon Save&Quit*/
    void writeFiles();

    // Creates
    /** @brief  Creates the representation of the lines in the graph*/
    void createGraphLines();

    /** @brief  Funtion that gives de distance*/
    static double haversine(double lat1, double lon1,
                            double lat2, double lon2);


    //Sets
    /** @brief  Set userName attribute.*/
    void setUsername(string username);

    /** @brief  Set walkingFac attribute.*/
    void setWalkingFac(int walkF);

    /** @brief  Set maxWalkDistattribute.*/
    void setMaxWalkDist(int maxWD);


    //Translates
    /** @brief  Translates coords.*/
    void translateCoord(string &str);
};

#endif //PROJ1_CONTROLLER_H
