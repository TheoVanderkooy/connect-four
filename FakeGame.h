//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"
enum ColVal;

class FakeGame{
public:
	FakeGame(int board[6][7], int p);
	void initialize(int board[6][7], int p);
	int checkWin(); // 1 = player1, 2 = player2, 0 = no winner (yet) -1 = tie (board is full)
	int checkSpotWin(int col, int row = -1); //-1 row = bottom one in that column
	int analysePosition(int col, int row, bool complete = false); //positive numbers are good, negative is good for other player
	int emptySpot(int col); //returns the bottom empty space in a given column (-1 = no empty space)
	void fakeMove(int col, int p);
	void undoMove(int col);
	int analyseCol(ColVal &colVal, int col, short depth, int row);
	int easyAiMove(); //makes a move with the easy ai
	int mediumAiMove(); //makes a move with the medium ai
	int aiMove(ColVal& val, short depth);
	int hardAiMove(); //makes a move with the hard ai
	int getNoOfCols();
private:
	int board[6][7]; //a copy of the board
	int p; //keeps track of which player it is
};