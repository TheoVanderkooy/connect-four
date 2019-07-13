//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

Game::Game(){ //default contstructor for game class
	this->p1Col = 12; //sets the player colours to the default values
	this->p2Col = 14;
	for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
			this->board[row][col] = 0; //initializes the game board to 0
		}
	}
	this->player1 = NULL; //sets the players and menus to null
	this->player2 = NULL;
	this->exitMenu = NULL;
	this->areYouSureMenu = NULL;
	this->onScreen = true; //sets the game to onscreen
	this->turns = 0; //sets the turns to 0
}
void Game::initialize(Player* player1, Player* player2, Menu* exitMenu, Menu* areYouSure){ //constructor for a game with a blank board
	this->player1 = player1; //saves the location of the two players
	this->player2 = player2;
	for (int row = 0; row < 6; row++){ 
		for (int col = 0; col < 7; col++){
			this->board[row][col] = 0; //initializes the game board to 0
		}
	}	
	this->turns = 0;
	this->exitMenu = exitMenu; //saves the locations of the exit and are you sure menus
	this->areYouSureMenu = areYouSure;
	this->onScreen = true; //the game is updated on screen if it is a real game
}
int Game::checkWin(){ //check if someone has won the game yet
	int count = 0;
	for (int row = 0; row < 6; row++){ //check the possible horizontal rows
		if (this->board[row][3] != 0){ //if the piece is not 0
			count = 1; //sets count to 1
			for (int col = 2; col >= 0; col--){
				if (this->board[row][col] == this->board[row][3]) count++; //increases count
				else break; // breaks when it is not the same as the center piece
			}
			for (int col = 4; col < 7; col++){
				if (this->board[row][col] == this->board[row][3]) count++; //increases count
				else break; 
			}
			if (count >= 4) return this->board[row][3]; //returns if someone has won
		}
	}
	for (int col = 0; col < 7; col++){ //checks all the possible vertical wins
		if (this->board[2][col] != 0 && this->board[2][col] == this->board[3][col]) { //if the two center pieces are the same and not 0
			if (this->board[2][col] == this->board[4][col]) { //if the piece above is the same
				if (this->board[2][col] == this->board[5][col] || this->board[2][col] == this->board[1][col]) //if the top piece or the one below are the same
					return this->board[2][col]; //returns the piece if they won			
			}
			else if (this->board[2][col] == this->board[1][col] && this->board[2][col] == this->board[0][col]) //if the center two are the same as the bottom two
				return this->board[2][col]; //returns the piece if they won
		}
	}
	for (int row = 0; row < 6; row++){ //check the possible up right diagonal wins
		if (this->board[row][3] != 0){ // if the middle is not 0
			count = 1; //sets count to 1
			for (int col = 2; col >= 0 && col >= 3 - row; col--){
				if (this->board[row - 3 + col][col] == this->board[row][3]) count++; //increases count if it is the same
				else break; //otherwise it breaks
			}
			for (int col = 4; col < 7 && col <= 8 - row; col++){
				if (this->board[row - 3 + col][col] == this->board[row][3]) count++; //increases count if it is the same
				else break; //otherwise it breaks
			}
			if (count >= 4) return this->board[row][3]; //returns if someone has won
		}
	}
	for (int row = 0; row < 6; row++){ //check the possible down right diagonal wins
		if (this->board[row][3] != 0){ //if the middle is not 0
			count = 1; //count is set to 1
			for (int col = 2; col >= 0 && col >= row - 2; col--){
				if (this->board[row + 3 - col][col] == this->board[row][3]) count++; //increases count if it is the same
				else break;
			}
			for (int col = 4; col < 7 && col <= row + 3; col++){
				if (this->board[row + 3 - col][col] == this->board[row][3]) count++; //increases count if it is the same
				else break;
			}
			if (count >= 4) return this->board[row][3]; //returns if someone has won
		}
	}
	if (this->board[5][0] != 0 && this->board[5][1] != 0 && this->board[5][2] != 0 && this->board[5][3] != 0 && this->board[5][4] != 0 && this->board[5][5] != 0 && this->board[5][6] != 0) return -1; //returns -1 if there is a tie
	return 0; //otherwise returns 0 (no winner)
}
void Game::drawPiece(int player, int col, int row){ //function to draw a piece on the board
	if (col < 0) col = 0; //makes sure the column is valid
	else if (col > 6) col = 6;
	if (row < 0) row = 0; //makes sure the row is valid
	else if (row > 5) row = 5;
	if (player < 1) player = 1; //makes sure the player is value
	setCursorColour(15, (player == 1 ? this->p1Col : this->p2Col)); //sets the cursor colour/position
	setCursorPosition(26 + col * 4, 21 - 3 * row);
	cout << "   "; //outputs the piece
	setCursorPosition(26 + col * 4, 20 - 3 * row);
	cout << "   "; //outputs the piece
	setCursorColour(); //resets the cursor colour
}
void Game::drawGame(){ //draws the game board
	clearScreen(); //clears the screen
	setCursorPosition(33, 1);
	cout << "Connect Four"; //outputs the game title
	for (int row = 0; row < 6; row++){ //for each row of the board
		for (int x = 25; x < 54; x++){ //outputs the  lines across the board at the top of each row
			setCursorPosition(x, 4 + 3 * row);
			cout << "-";
		}
		for (int col = 0; col < 8; col++){ //for each column
			setCursorPosition(25 + 4 * col, 5 + 3 * row);
			cout << "|"; //outputs the sides of each column
			setCursorPosition(25 + 4 * col, 6 + 3 * row);
			cout << "|"; //outputs the sides of each column
		}
	}
	for (int x = 25; x < 54; x++){ //outputs the line across the bottom of the board
		setCursorPosition(x, 22);
		cout << "-";
	}
	//outputs the pieces on the board if there are any
	for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
			if (this->board[row][col] == 1) drawPiece(1, col, row); //outputs a piece if it is player 1
			else if (this->board[row][col] == 2) drawPiece(2, col, row); //outputs a piece if it's player 2
		}
	}
	setCursorPosition(23, 24); 
	cout << "Press ESC to pause/exit the game.";
	(*this->player1).outputSideText(1); //outputs the controls on the side for each player
	(*this->player2).outputSideText(2);
}
int Game::getPlayerMove(int player){ //gets a move frome the player	
	int move;
	this->turns++; //increases the turns counter
	do{ 
		if (player <= 1){
			move = (*this->player1).getMove(1); //gets the move from the player
		} 
		else {
			move = (*this->player2).getMove(2); //gets the move from player 2
		}
		if (move == 0){
			int exit = (*this->exitMenu).getSelection(); //gets the selection from the exit menu
			if (exit == 0 && !(*this->areYouSureMenu).getSelection()){ //exit
				this->onScreen = 0; //sets onscreen to false so the game doesnt get redrawn
				return -2; //signals that the game was ended
			}
			if (this->onScreen) this->drawGame(); //redraws the board before continueing
			//continues if they arent sure
		}
		else {
			if (board[5][move - 1] != 0) { //if there is already a piece in the top of the column
				move = 0; //move is set to 0 so it will keep getting their move
			}
			else { //if the column is free
				for (int row = 0; row < 6; row++){
					if (this->board[row][move - 1] == 0) { //if the space is free
						this->board[row][move - 1] = (player <= 1 ? 1 : 2); //sets it to a player
						if (this->onScreen) this->drawPiece(player, move - 1, row); //draws the piece
						break; //exits the loop
					}
				}
			}
		}
	} while (move == 0); //repeats until they do a real move
	return this->checkWin(); //checks if anyone has won yet
}
void Game::resetGame(){ //resets the game board
	for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
			this->board[row][col] = 0; //initializes the game board to 0
		}
	}
	this->turns = 0;
}
void Game::endGame(int winner){ //function to end the game    (-2 = game exit, -1 = tie, 1 = p1, 2 = p2)
	if (winner == -2){ //if winner is -2 (exit)
		//does nothing and just goes back to the main menu
	}
	else if (winner == -1){ //if winner is -1 (tie)		
		setCursorPosition(6, 24); 
		cout << "The game was a Tie. Press any key to return to the main Menu: "; //outputs that there was a tie
		_getch(); //waits for use input before returning to the main menu
	}
	else if (winner == 1){ //if winner is 1 (p1)
		(*this->player1).endGame(true, this->turns, (*this->player2).getAiLevel()); //save the win for player 1
		(*this->player2).endGame(false, this->turns, (*this->player1).getAiLevel()); //saves the loss for player 2
		string p1name = (*this->player1).getName(); //gets the player's name
		setCursorPosition((p1name.size() >= 30 ? 0 :(30-p1name.size())/2), 24); 
		setCursorColour(this->p1Col); //sets the text colour to the player's name
		cout << (p1name.size() >= 30? p1name.substr(0,30) : p1name); //outputs the player's name
		setCursorColour(); //resets the text colour
		cout << " Wins! Press any key to return to the Main Menu: ";
		_getch(); //waits for use input before returning to the main menu
	}
	else if (winner == 2){ //if winner is 2 (p2)
		(*this->player1).endGame(false, this->turns, (*this->player2).getAiLevel()); //save the loss for player 1
		(*this->player2).endGame(true, this->turns, (*this->player1).getAiLevel()); //saves the win for player 2
		string p2name = (*this->player2).getName(); //gets the player's name
		setCursorPosition((p2name.size() >= 30 ? 0 : (30 - p2name.size()) / 2), 24);
		setCursorColour(this->p2Col); //sets the text colour to the player's name
		cout << (p2name.size() >= 30 ? p2name.substr(0, 30) : p2name); //outputs the player's name
		setCursorColour(); //resets the text colour
		cout << " Wins! Press any key to return to the Main Menu: ";
		_getch(); //waits for use input before returning to the main menu
	}
}
void Game::game(){ //the actual game
	this->resetGame(); //resets the game
	if (this->onScreen) {
		this->drawGame(); //draws the game board
	}
	int winner = 0;
	do {
		winner = this->getPlayerMove(1); //gets the move from player 1
		if (winner == 0){ //if player 1 didn't win
			winner = this->getPlayerMove(2); //gets the move from player 2
		}
	} while (winner == 0); //repeats until there is a winner
	switch (winner){
	case -2: //if the game is ended
		this->endGame(-2);
		break;
	case -1: //if there was a tie
		this->endGame(-1); //there was a tie
		break;
	case 1: //if player 1 wins
		this->endGame(1);
		break;
	case 2: //if player 2 wins
		this->endGame(2);
		break;
	}
}