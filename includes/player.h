#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <functional>
#include "diceset.h"
#include <iostream>

class Player
{
public:

    Player (std::string id, std::function<DiceSet(std::vector<Player*>)>strategy){
        this->id = id;
        this->chooseSet = strategy;
    }

    int getPoints (){
        return points;
    }

    void incPoints (int increment){
        points += increment;
    }

    void resetPoints (){
        points = 0;
        roll_log.clear();
    }

    bool operator < (const Player& pr) const
    {
        return (points < pr.points);
    }

    std::ostream & operator << (std::ostream &out)
    {
        out << id;
        return out;
    }

    std::function<DiceSet(std::vector<Player*>)>chooseSet;
    std::vector<int> roll_log;

    std::string getId(){return id;}

private:
    std::string id;
    int points = 0;



};

#endif // PLAYER_H
