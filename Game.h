//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"
#include"Player.h"


class Game{ //class for the game
	friend class Player;
public:
	Game();
	void initialize(Player* player1, Player* player2, Menu* exitMenu, Menu* areYouSure);
	void resetGame();
	int checkWin(); // 1 = player1, 2 = player2, 0 = no winner (yet) -1 = tie (board is full)
	void game();
	int getPlayerMove(int player);  //-2 = endgame, -1 = tie, 1 = p1, 2 = p2
	void endGame(int winner); //-2 = endgame, -1 = tie, 1 = player 1, 2 = player 2
	void drawGame();
	void drawPiece(int player, int col, int row); 
	int p1Col; //player 1 colour setting
	int p2Col; //player 2 colour setting
private:
	Player* player1;
	Player* player2;
	Menu* exitMenu;
	Menu* areYouSureMenu;
	bool onScreen;
	int board[6][7];  //6 rows, 7 columns, col[0] = left, row[0] = bottom    0 = blank, 1 = player 1, 2 = player 2
	int turns;
};