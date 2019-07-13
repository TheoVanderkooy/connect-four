//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

class PlayerAccount{ //class to keep track of player accounts
public:
	PlayerAccount(string name = "[no name available]");
	void save(string name, int wins[], int losses[], int totalWinTurns[]);
	void changeName(string name);
	void endGame(bool win, int turns, int aiLevel);
	string getName();
	int getWins(int difficulty);
	int getLosses(int difficulty);
	int getTotalTurns(int difficulty);
	double getTurnsPerWin(int difficulty);
private:
	string name;
	int wins[4]; //0 = easy AI, 1 = medium AI, 2 = hard AI, 3 = against players
	int losses[4]; //see above
	int totalWinTurns[4]; //total number of turns in all winning games (to keep track of average turns/win)
};