//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

PlayerAccount::PlayerAccount(string name){ //constructor for player account class
	this->name = name; //saves the name
	for (int i = 0; i < 4; i++){ //initializes all the stats to 0
		this->wins[i] = 0;
		this->losses[i] = 0;
		this->totalWinTurns[i] = 0;
	}
}
void PlayerAccount::changeName(string name){ //function for changing the name
	this->name = name; //saves the name
}
void PlayerAccount::endGame(bool win, int turns, int aiLevel){
	if (win){ //if they won
		this->wins[aiLevel]++; //increases the number of wins
		this->totalWinTurns[aiLevel] += turns; //increases the total turns of wining games
	}
	else this->losses[aiLevel]++; //if they lost increases the number of loses
}
string PlayerAccount::getName(){ //function to get the name of a player
	return this->name; 
}
int PlayerAccount::getWins(int difficulty){ //gets the number of wins
	return this->wins[difficulty]; //returns the wins on that difficulty
}
int PlayerAccount::getLosses(int difficulty){ //gets the number of losses
	return this->losses[difficulty]; //returns the number of losses on that difficulty
}
int PlayerAccount::getTotalTurns(int difficulty){ //gets the total number of turns of won games
	return this->totalWinTurns[difficulty]; 
}
double PlayerAccount::getTurnsPerWin(int difficulty){ //gets the average turns per win
	if (wins[difficulty] == 0) return 0; //returns 0 if the number of wins is 0
	else return  (static_cast<double> (totalWinTurns[difficulty]) / static_cast<double> (wins[difficulty])); //returns the average turns per win rounded to 2 decimals
}
void PlayerAccount::save(string name, int wins[], int losses[], int totalWinTurns[]){//function to set a 
	this->name = name; //saves the name
	for (short i = 0; i < 4; i++){ //for each difficulty
		this->wins[i] = wins[i]; //saves the number of wins, losses and total turns
		this->losses[i] = losses[i];
		this->totalWinTurns[i] = totalWinTurns[i];
	}
}