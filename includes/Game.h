#pragma once

class Game
{
public:
	Game()
	{
		this->running = false;
		this->total_players = 0;
	}

	~Game() {}

	/**
	* true  - keep running
	* false - stop execution
	*/
	bool run();

	void setPlayers(int num_players);
private:
	bool running;

	int total_players;
};
