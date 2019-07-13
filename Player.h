//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

class Player{ //class for the players
	friend class Game;
public:
	Player(Game* game);
	void setPlayer(int aiLevel, PlayerAccount* account = NULL);
	void outputSideText(int player);
	int getMove(int p); //1 to 7 for the columns, 0 is the exit/pause menu	
	void endGame(bool win, int turns, int aiLevel);
	void increaseSeletion();
	void decreaseSelection();
	int getAiLevel();
	string getName();
private:
	int aiLevel;
	Game* game;
	PlayerAccount* account;
	int selection;
};