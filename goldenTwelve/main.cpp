#include <iostream>
#include <vector>
#include <algorithm>
#include "player.h"
using namespace std;


void makeRolls (std::vector<std::pair<DiceSet,Player*>> &pl_n_dice){

    // make the rolls
    for(auto &pair : pl_n_dice){
        pair.second->roll_log.push_back(pair.first.roll());
    }


    // sort from last value to most
    std::sort(pl_n_dice.begin(),pl_n_dice.end(), [](std::pair<DiceSet,Player*> p1, std::pair<DiceSet,Player*> p2) -> bool {
        if(p1.second->roll_log.back() != p2.second->roll_log.back()){
            return p1.second->roll_log.back() < p2.second->roll_log.back();
        }

        return p1.first.getType().value < p2.first.getType().value;
    });

}

int howManyDraws (std::vector<std::pair<DiceSet,Player*>> &pl_n_dice){
    auto it1 = pl_n_dice.end() -1;
    auto it2 = it1 -1;

    int num_draws = 0;
    while(it1->second->roll_log.back() == it2->second->roll_log.back() &&
       it1->first.getType().value == it2->first.getType().value){
        --it1;
        --it2;
        ++num_draws;
    }
    std::cout << "DRAW[" << num_draws << "]" << endl;
    return num_draws;
}

void runRound (std::vector<Player*> &leaderboard){

    std::vector<std::pair<DiceSet,Player*>> pl_n_dice;

    // commit each player with a set of dice
    for (auto &pl : leaderboard) {
        pl_n_dice.push_back(make_pair(pl->chooseSet(leaderboard),pl));
    }

    int draws = 0;
    do{
        makeRolls(pl_n_dice);

        draws = howManyDraws(pl_n_dice);
        if(draws != 0){
            // create a sub vector where picks only the end ones with draws
            std::vector<std::pair<DiceSet,Player*>> new_vec (pl_n_dice.end() - draws,pl_n_dice.end());
            pl_n_dice = new_vec;
        }
    }while(draws != 0);

    auto winner = pl_n_dice.end()-1;
    //winner->second->incPoints(winner->first.getType().value);
    winner->second->incPoints(1);
    std::sort(leaderboard.begin(),leaderboard.end());
}

void printLeaderBoard (std::vector<Player*> &leaderboard){
    std::cout << "Leaderboards:" << endl;

    // Print leaderboard
    for(auto player : leaderboard){
        std::cout << player->getId() << ": [";

        for(auto it = player->roll_log.begin(); it != player->roll_log.end(); ++it)
            std::cout << *it << ",";

        std::cout << "]" << " Total: " << player->getPoints() << endl;
    }
}

Player * checkForWinner (std::vector<Player*> &leaderboard){
    for(auto player: leaderboard){
        if(player->getPoints() >= 12){
            return player;
        }
    }

    return nullptr;
}

std::string runGame (std::vector<Player*> &leaderboard){
    Player *winner;
    while((winner = checkForWinner(leaderboard)) == nullptr){
        runRound(leaderboard);
    }

    printLeaderBoard(leaderboard);

    cout << "The winner is:" << winner->getId() << endl;
    return winner->getId();
}

int main()
{
    DiceSet s3d4(3,DiceSet::Type(std::pair<int,int>(1,4),DiceSet::Type::COPPER));
    DiceSet s2d6(2,DiceSet::Type(std::pair<int,int>(1,6),DiceSet::Type::SILVER));
    DiceSet s1d12(1,DiceSet::Type(std::pair<int,int>(1,12),DiceSet::Type::GOLD));

    std::function<bool(Player&,Player&)> set_comp = [](Player &p1,Player &p2) -> bool {
        return p1.getPoints() < p2.getPoints();
    };



    auto chooseOnlyD4 = [s3d4] (std::vector<Player*>)-> DiceSet{return s3d4;};
    auto chooseOnlyD6 = [s2d6] (std::vector<Player*>)-> DiceSet{return s2d6;};
    auto chooseOnlyD12 = [s1d12] (std::vector<Player*>)-> DiceSet {return s1d12;};

    std::vector<Player*> players;

    Player p1("Only4",chooseOnlyD4);
    Player p2("Only6",chooseOnlyD6);
    Player p3("Only12",chooseOnlyD12);

    p1.chooseSet(players);

    players.push_back(&p1);
    players.push_back(&p2);
    players.push_back(&p3);

    runGame(players);

    return 0;
}
