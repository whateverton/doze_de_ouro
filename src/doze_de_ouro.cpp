
#include "Game.h"
#include "regras.h"

#include <iostream>

int main()
{
    Game* currentGame = new Game();

    std::cout << GAME_RULES << std::endl;

    do
    {
        std::cout << "Digite a quantidade de jogadores: " << std::endl;

        char buffer[999 + 1]; // Max 999 players
        std::cin.getline(buffer, sizeof(buffer) - 1);

        currentGame->setPlayers(atoi(buffer));
    } while (currentGame->run());
}
