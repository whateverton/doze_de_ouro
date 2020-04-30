#include "Game.h"

#include <iostream>

bool Game::run()
{
	if (!this->running)
	{
		this->running = true;

		/*
		O JOGO VAI AQUI
		*/
	}

	this->total_players = 0;
	this->running = false;
	
	char keep_playing[1 + 1];
	do {
		std::cout << "Deseja encerrar o jogo? (Y/N)" << std::endl;
		std::cin.getline(keep_playing, 2);
	} while ((keep_playing[0] != 'y') && (keep_playing[0] == 'n') && (keep_playing[0] != 'Y') && (keep_playing[0] == 'N'));

	if ((keep_playing[0] == 'y') || (keep_playing[0] == 'Y'))
		return true;
	else
		return false;
}
void Game::setPlayers(int num_players)
{
	if(!this->running)
		this->total_players = num_players;
}
