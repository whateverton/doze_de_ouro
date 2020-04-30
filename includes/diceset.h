#ifndef DICESET_H
#define DICESET_H

#include <stdlib.h>
#include <chrono>
#include <random>

class DiceSet
{
public:

    class Type{
    public:
        enum VALUE{
            COPPER = 1,
            SILVER = 2,
            GOLD   = 3
        };

        Type(std::pair<int,int>range,VALUE v){
            this->range = range;
            this->value = v;
        }

        int value;
        std::pair<int,int> range;

    };

    DiceSet(int num_dice, Type type) : type(std::pair<int,int>(1,4),Type::COPPER){
        this->type = type;
        this->num_dice = num_dice;
    }

    int roll (void){
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);

        std::uniform_int_distribution<int> distribution(type.range.first,type.range.second);

        int sum = 0;
        for(int i = 0; i< num_dice;++i){
            sum += distribution(generator);
        }
        return sum;
    }

    Type getType (){return type;}


private:

    Type type;
    int num_dice;

};

#endif // DICESET_H
