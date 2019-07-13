//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

Player::Player(Game* game){ //constructor for the player class
	this->game = game; //saves the pointer to the game
	this->aiLevel = true; //saves it as an ai
	this->account = NULL; //sets the account to NULL
	this->selection = 1;
}
void Player::setPlayer(int aiLevel, PlayerAccount* account){ //functio nto set the player to an account
	this->aiLevel = aiLevel;
	if (aiLevel == againstPlayer) this->account = account; //if the ai level is 0 (player) the account is saved
	else this->account = NULL; //if the ai level is not a player the account is set to a NULL pointer
}
void Player::outputSideText(int player){ //function to output the text on the side of the screen
	int x, c, nameLength;
	const int y = 6;
	string name;
	if (player <= 1) {
		x = 2; //if it is player 1 the x location is set to 2
		c = (*this->game).p1Col; //gets the colour from the game
	}
	else{
		x = 57; //if it is player 2 the x location is set to 57
		c = (*this->game).p2Col; //gets the colour from the game
	}
	setCursorPosition(x + 6, y); //sets the cursor location
	setCursorColour(c); //sets the cursor colour
	cout << "Player " << (player <= 1 ? '1' : '2'); //outputs if it is player two or player 1
	setCursorColour(); //resets the cursor colour
	if (this->aiLevel == againstPlayer){ //if it is a human player
		name = (*this->account).getName(); //gets the name of the account
		nameLength = name.size(); //finds the length of the name of the player
		if (nameLength >= 20) { //if the name is more than 20 characters
			setCursorPosition(x, y+1); //sets the cursor position
			cout << name.substr(0, 20); //outputs the first 20 characters of the account name
		}
		else {
			setCursorPosition(x+((20-name.size())/2), y+1); //sets the cursor position
			cout << name; //outputs the account name
		}
		if (player <= 1){ //if it is player 1 outputs the sidebar instructions
			setCursorPosition(x + 2, y + 3); //sets the cursor position
			cout << "Press A and D to";
			setCursorPosition(x + 2, y + 4); //sets the cursor position
			cout << "select a column.";
			setCursorPosition(x + 2, y + 5); //sets the cursor position
			cout << "Use S to select.";
		}
		else{ //if it is player 2 outputs the sidebar instructions
			setCursorPosition(x + 2, y + 3); //sets the cursor position
			cout << "Press J and L to";
			setCursorPosition(x + 2, y + 4); //sets the cursor position
			cout << "select a column.";
			setCursorPosition(x + 2, y + 5); //sets the cursor position
			cout << "Use K to select.";
		}
	}
	else { //if it is an ai
		setCursorPosition(x + 6, y+1); //sets the cursor location
		switch (this->aiLevel){ //outputs if the ai is easy, medium or hard
		case againstEasy: //outputs if it is easy
			cout << "Easy AI ";
			break;
		case againstMedium: //outputs if it is medium
			cout << "Medium AI";
			break;
		case againstHard: //outputs if it is hard
			cout << "Hard AI ";
			break;
		default:;
		}
	}
}
void Player::increaseSeletion(){ //increases the selection
	if (this->selection == 7) this->selection = 1; //if it is 7 it is set to 1
	else this->selection++; //otherwise it is increased
}
void Player::decreaseSelection(){ //decreases the selection
	if (this->selection == 1) this->selection = 7; //if it is 1 it is set to 7
	else this->selection--; //otherwise it is decreased by 1
}
void Player::endGame(bool win, int turns, int aiLevel){ //function that is called at the end of a game
	if (this->aiLevel == againstPlayer){ //if it is a human player
		(*this->account).endGame(win, turns, aiLevel); //the info is passed on to the account
	}
}
int Player::getAiLevel(){ //returns the ai level
	return this->aiLevel;
}
string Player::getName(){ //function that returns the name of the player
	if (this->aiLevel == againstPlayer){ //returns the player's name
		return (*this->account).getName(); //gets the name from the associated account
	}
	else if (this->aiLevel == againstEasy){
		return "Easy AI"; //returns the name of the easy ai
	}
	else if (this->aiLevel == againstMedium){
		return "Medium AI"; //returns the name of the medium ai
	}
	else if (this->aiLevel == againstHard){
		return "Hard AI"; //returns the name of the hard ai
	}
	else return "[ERROR_NAME]";  //returns ERROR_NAME if there is an error
}
int Player::getMove(int p){ //gets the move from the player
	if (this->aiLevel == againstPlayer){
		short left;
		short right;
		short select;
		if (p <= 1){ //uses player 1 controls
			left = leftKey;
			right = rightKey;
			select = downKey;
		}
		else { //uses player 2 controls
			left = p2Left;
			right = p2Right;
			select = p2Down;
		}
		this->selection = 4;
		int input;
		int c = (p <= 1 ? (*this->game).p1Col : (*this->game).p2Col);
		do {
			for (int col = 0; col < 7; col++){ //for each column
				setCursorPosition(26 + 4 * col, 3); 
				if (this->selection == col + 1){
					setCursorColour(15, c);
				}
				cout << " " << col + 1 << " "; //outputs the numbers at the top of the screen
				setCursorColour();
			}
			_flushall(); //clears the input buffer
			input = _getch(); 
			if (input == left) this->decreaseSelection(); //decreases the selection
			else if (input == right) this->increaseSeletion(); //increases the selection
			else if (input == escKey) return 0; //returns 0 if the escape key is pressed
			//other input is ignored
		} while (input != select);
		return this->selection; //returns the selection
	}
	else if (this->aiLevel == againstEasy){ //if it is an easy ai
		clock_t start = clock();
		FakeGame ai((*this->game).board, p);
		short move = ai.easyAiMove() + 1; //gets the ai move for an easy ai
		clock_t end = clock();
		if (end - start < moveTime){ //makes sure there is a slight delay
			Sleep(moveTime - end + start);
		}
		return move; 
	}
	else if (this->aiLevel == againstMedium){ //if it is a medium ai
		clock_t start = clock();
		FakeGame ai((*this->game).board, p);
		short move = ai.mediumAiMove() + 1; //gets the ai move for an easy ai
		clock_t end = clock();
		if (end - start < moveTime){ //makes sure there is a slight delay
			Sleep(moveTime - end + start);
		}
		return move;
	}
	else{ //if it is a hard ai
		clock_t start = clock();
		FakeGame ai((*this->game).board, p);
		short move = ai.hardAiMove() + 1; //gets the ai move for a hard ai (depth of 4)
		clock_t end = clock();
		if (end - start < moveTime){ //makes sure there is a slight delay
			Sleep(moveTime - end + start);
		}
		return move;
	}
}