//
// Created by 35196 on 26/03/2022.
//

#ifndef TRABALHODA1_TRUCK_H
#define TRABALHODA1_TRUCK_H


using namespace std;

class Truck {
private:
    int id;
    int volMax;
    int weightMax;
    int cost;
    int RankingWei;
public:
    int getRankingWei() const;

    void setRankingWei(int rankingWei);

    int getRankingVol() const;

    void setRankingVol(int rankingVol);

private:
    int RankingVol;

public:
    //Constructors
    /** @brief  Default constructor.*/
    Truck();

    /** @brief Received the necessary attributes to create a Order object.*/
    Truck(const int &id, const int &volMax, const int &weightMax, const int &cost);

    //Deconstructors
    /** @brief  Default destructor.*/
    ~Truck();

    //Gets
    /** @brief  Get id attribute.*/
    const int &getId() const;

    /** @brief  Get volMax attribute.*/
    const int &getVolMax() const;

    /** @brief  Get weightMax attribute.*/
    const int &getWeightMax() const;

    /** @brief  Get cost attribute.*/
    const int &getCost() const;




    //Sets
    /** @brief  Set id attribute.*/
    void setId(const int &id);

    /** @brief  Set volMax attribute.*/
    void setVolMax(const int &volMax);

    /** @brief  Set weightMax attribute.*/
    void setWeightMax(const int &weightMax);

    /** @brief  Set cost attribute.*/
    void setCost(const int &cost);



};
#endif //TRABALHODA1_TRUCK_H
