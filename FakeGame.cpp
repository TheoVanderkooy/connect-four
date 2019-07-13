//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

FakeGame::FakeGame(int board[6][7], int p){
	for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
			this->board[row][col] = board[row][col]; //initializes the fake game board to the board used as the parameters
		}
	}
	this->p = p; //saves which player it is
}
void FakeGame::initialize(int board[6][7], int p){ //function to initialize the fake game
	for (int row = 0; row < 6; row++){
		for (int col = 0; col < 7; col++){
			this->board[row][col] = board[row][col]; //initializes the fake game board to the board used as the parameters
		}
	}
	this->p = p; //saves which player it is
}
int FakeGame::checkWin(){ //check if someone has won the game yet
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
int FakeGame::checkSpotWin(int col, int row) { //checks if a move causes a win
	if (row == -1) row = emptySpot(col) - 1; 
	if (row == -1) return -1; // the row is empty returns -1 to signal 
	if (row == -1) row = 5; //if the column is full it is the top row
	if (this->board[row][col] == 0) return 0; //returns 0 if the spot is 0
	
	int count = 1;

	for (short i = row - 1; i >= 0; i--){ //counts down from the spot
		if (this->board[i][col] == this->board[row][col]) count++; //increases count if the spot is the same as the start
		else break; //breaks when it isnt
	}
	for (short i = row + 1; i < 6; i++){ //counts up from the spot
		if (this->board[i][col] == this->board[row][col]) count++; //increases count if the spot is the same as the start
		else break; //breaks when it isnt
	}
	if (count >= 4) return this->board[row][col]; //returns the value if the person won
	count = 1;
	for (short i = col - 1; i >= 0; i--){ //left from the spot
		if (this->board[row][i] == this->board[row][col]) count++; //increases count
		else break;
	}
	for (short i = col + 1; i < 7; i++){ //right from the spot
		if (this->board[row][i] == this->board[row][col]) count++; //increases count
		else break;
	}
	if (count >= 4) return this->board[row][col]; //returns the value if the person won
	count = 1;
	for (short i = col - 1; i >= 0; i--){ //left from the spot going down
		if (this->board[row][col] == this->board[row + i - col][i]) count++;
		else break;
	}
	for (short i = col+- 1; i < 7; i++){ //right from the spot going up
		if (this->board[row][col] == this->board[row + i - col][i]) count++;
		else break;
	}
	if (count >= 4) return this->board[row][col]; //returns the value if the person won
	count = 1;
	for (short i = col - 1; i >= 0; i--){ //left from the spot going up
		if (this->board[row][col] == this->board[row + col - i][i]) count++;
		else break;
	}
	for (short i = col + -1; i < 7; i++){ //right from the spot going down
		if (this->board[row][col] == this->board[row + col - i][i]) count++;
		else break;
	}
	if (count >= 4) return this->board[row][col]; //returns the value if the person won
	return 0; //returns 0 if noone won
}
int FakeGame::analysePosition(int col, int row, bool complete){ //funcion to analyse a given position on the game board 
	//-1 = off board, 0 = emty, 
	int rUp[7]; //keeps track of the diagonal from the bottom left to the top right
	int rDown[7]; //keeps track of the diagonal from the top left to the bottom right
	
	int vValue, hValue, urValue, drValue;
	int urCount = 0, drCount = 0;

	//isolates the diagonals
	for (int c = 0; c < 7; c++){ //for each column
		if (row + c - col >= 0 && row + c - col < 6) {
			rUp[c] = this->board[row + c - col][c]; //saves the diagonal
			urCount++; //increases the counter of the up right diagonal
		}
		else rUp[c] = -1; //signals the position is off the board
		if (row + col - c >= 0 && row + col - c < 6) {
			rDown[c] = this->board[row + col - c][c]; //saves the diagonal
			drCount++; //increases the counter of down right diagonal
		}
		else rDown[c] = -1; //signals that the position is off the board
	}

	short first = 0; //what the first piece encountered is 
	short count = 5 - row; //how many spaces are available
	short pieces = 0; //how many pieces there are of type 'first'
	short inRow; //how many there are in a row

	//analyzes the vertical
	for (int r = row; r >= 0; r--){
		if (first == 0 && board[r][col] != 0) { //if it is the first piece that is not 0
			first = board[r][col]; //first is set to the current piece
			pieces++; //number of pieces is increased
			count++; //count is increased
		}
		else if (board[r][col] == 0) { //if the current piece is 0
			count++; //count is increased
		}
		else if (first != 0 && board[r][col] != first) { //if 'first' is not 0 but the current space is not the same as first
			break; //breaks the loop
		}
		else if (first != 0 && board[r][col] == first) { //if the current space is the same as first
			count++; //increases the counter
			pieces++; //increases the pieces counter
		}
	}
	if (count < 4) { //if count is less than 4 noone can win vertically
		vValue = useless; //the vertical value is set to 0 
	}
	else if (pieces >= 3) { //if (someone) can win on the next turn in this spot
		if (first == this->p) vValue = threeOtherPieces; //saves if it is the ai that will win
		else vValue = -threeOtherPieces; //saves if it is the player who will win
		if (complete == false) return vValue; //immediately returns the vValue because the piece must be blocked or played to win if 'complete' is false
	}
	else if (pieces == 2) { //if someone can win in two turns
		if (first == this->p) vValue = twoOtherPieces; //saves if it is the ai that will win
		else vValue = -twoOtherPieces; //saves if it is the player who will win
	}
	else if (pieces == 1) { //if there is only 1 other piece vertically
		if (first == this->p) vValue = oneOtherPiece; //saves if it is the ai has the advantage
		else vValue = -oneOtherPiece; //saves if it is the player has the piece
	}
	else if (pieces == 0) { //saves if the row is empty
		vValue = emptyRow;
	}

	//analyse the horizontal
	first = 0; //resets the first and the pieces to 0
	pieces = 0;
	count = 0;
	short count2 = -1;
	short pieces2 = -1;
	for (int c = col; c >= 0; c--) { //from the selected position to the start
		if (first == 0) { //if first is still 0
			if (board[row][c] == 0) { //if the board position is also 0
				count++;
			}
			else {
				first = board[row][c]; //first is saved as the current position
				pieces++; //pieces is increased to 1
				count++; //the counter is increased
			}
		}
		else { //if first is not 0
			if (board[row][c] == 0) { //if the board is also 0
				count++; //count is increased
			}
			else if (board[row][c] == first) { //if the current position is the same as first
				count++; //count is increased
				pieces++; //pieces is increased
			}
			else { //if the board position is not the same
				break; //breaks the loop
			}
		}
	}
	for (int c = col + 1; c < 7; c++) { //goes to the end from the selected column
		if (first == 0) { //if first is still 0
			if (board[row][c] == 0) { //if the board position is also 0
				count++;
			}
			else {
				first = board[row][c]; //first is saved as the current position
				pieces++; //pieces is increased to 1
				count++; //the counter is increased
			}
		}
		else { //if first is not 0
			if (board[row][c] == 0) { //if the board is also 0
				count++; //count is increased
			}
			else if (board[row][c] == first) { //if the current position is the same as first
				count++; //count is increased
				pieces++; //pieces is increased
			}
			else { //if the board position is not the same
				short blanks = 0; //counts the number of blanks going back
				for (short c2 = c-1; c2 >= 0; c2--) { 
					if (board[row][c2] == 0) blanks++; //if the position is blank increase the blank counter
					else { //if it is not blank
						if (c2 > col) { //if the current column is past the selected column
							blanks = -1; //blanks is set to negative to signify that it should be ignored
						}
						break; 
					}
				}
				if (blanks == -1) break; //breaks if blanks is negative 
				if (blanks + 7 - c < 4) { //if the spaces to the end of the row is less than 4
					break; //no point considering the other player
				}
				else {
					if (count < 4) { //if the count so far is less than 4
						first = board[row][c]; //saves the new first position
						count = blanks + 1; //the count is set again
					}
					else{
						count2 = count; //sets count2 to count
						pieces2 = pieces; //sets pieces2 to pieces
						pieces = 1; //pieces and count are saved
						count = blanks + 1;
						first = board[row][c]; //first is reset
					}
				}
			}
		}
	}
	if (count2 != -1 && count < 4){ //swaps the count back if there werent enough spaces for count2
		count = count2;
		pieces = pieces2;
		first = (first == 1 ? 2 : 1);
		count2 = -1;
		pieces2 = -1;
	}
	int hValue2 = 0;
	if (count2 != -1){ //if both players can use this spot
		inRow = 0;
		for (int c = col - 1; c >= col - count2 ; c--){ //from the center to the beginning
			if (board[row][c] == (first == 1 ? 2 : 1)) inRow++; //if the board position is the same as not first inRow is increased
			else break; //otherwise the loop is broken
		}
		if (inRow >= 3) { //if there are 3 in a row from the current piece
			if (first == this->p) hValue2 = -threeOtherPieces; //saves if it is the player that will win
			else hValue2 = threeOtherPieces; //saves if it is the ai who will win
			if (!complete) return hValue2; //immediately returns if complete is false
		}
		else if (inRow == 2) { //if there are 2 in a row from the current piece
			if (col >= 3 && board[row][col - 3] == 0) {
				if (first == this->p) hValue2 = -twoPiecesBothEnds; //saves if it is the player has advantage
				else hValue2 = twoPiecesBothEnds; //saves if it is the ai who has advantage
			}
			else {
				if (first == this->p) hValue2 = -twoOtherPieces; //saves if it is the player advantage
				else hValue2 = twoOtherPieces; //saves if it is the ai advantage
			}
		}
		else if (inRow == 1) { //if inRow is 1			
			if (col < 3 || board[row][col - 3] == 0 || board[row][col - 3] == first) { //if there is piece, blank, blank/other piece
				if (first == this->p) hValue2 = -oneOtherPiece; //saves if it is the player that will win
				else hValue2 = oneOtherPiece; //saves if it is the ai who will win
			}
			else { //otherwise there must be a friendly piece there
				if (first == this->p) hValue2 = -twoOtherPieces; //saves if it is the player that has the advantage
				else hValue2 = twoOtherPieces; //saves if it is the ai that has the advantage
			}
		}
		else { //if inRow is 0
			if (col >= 3 && board[row][col - 2] != (first == 1 ? 2 : 1) && board[row][col - 3] != (first == 1 ? 2 : 1)) hValue2 = useless; //if there are 3 empy spaces over it is useless
			else if (board[row][col - 2] == (first == 1 ? 2 : 1)){ 
				if (col < 3 || board[row][col - 3] != (first == 1 ? 2 : 1)){ //if there is one other piece
					if (first == this->p) hValue2 = -oneOtherPiece; //saves if it is the player that will win
					else hValue2 = oneOtherPiece; //saves if it is the ai who will win
				}
				else { //if there are two other pieces
					if (first == this->p) hValue2 = -twoOtherPieces; //saves if it is the player that will win
					else hValue2 = twoOtherPieces; //saves if it is the ai who will win
				}
			}
		}
	}
	if (pieces < 0 || count < 4) { //if pieces is negative or the count is less than 4
		hValue = useless; //the hvalue is set to useless
	}
	else if (pieces == 0) { //if pieces is 0
		hValue = emptyRow; //the hvalue is set to the empty row
	}
	else if (pieces >=3 && pieces == count + 1) { //if the number of pieces is one less than the count, which is 4 or more
		if (first == this->p) hValue = threeOtherPieces; //saves if it is the ai that will win
		else hValue = -threeOtherPieces; //saves if it is the player who will win
		if (!complete) return hValue; //returns immediately of complete is false
	}
	else { 
		inRow = 0; //the number in a row is set to 1
		if (count2 == -1) { //if count2 is negative
			for (int c = col - 1; c >= 0; c--) { //goes backwards from the center
				if (board[row][c] == first) inRow++; //if the board position is first inRow is increased
				else break; //otherwise the loop is broken
			}
		}
		for (int c = col+1; c < 7; c++) { //from the selected piece to the end
			if (board[row][c] == first) inRow++; //if it is the same as the first the row is increased
			else break; //otherwise it breaks the loop
		}
		if (inRow >= 3) { //if there are 3 in a row from the current piece
			if (first == this->p) hValue = threeOtherPieces; //saves if it is the ai that will win
			else hValue = -threeOtherPieces; //saves if it is the player who will win
			if (!complete) return hValue; //returns immediately complete is false
		}
		else if (inRow == 2) { //if there are 2 in a row from the current piece
			if ((col >= 3 && board[row][col-1] == first && board[row][col-2] == first && board[row][col-3] == 0) //if there are piece, piece, blank to the left
				|| (col <= 3 && board[row][col+1] == first && board[row][col+2] == first && board[row][col+3] == 0)  //if there is piece, piece, blank to the right
				|| (col >= 2 && col <= 4 && board[row][col+1] == first && board[row][col-1] == first && board[row][col+2] == 0 && board[row][col-2] == 0)){ 
				if (first == this->p) hValue = twoPiecesBothEnds; //saves that the ai has the advantage
				else hValue = -twoPiecesBothEnds; //the player has the advantage
			} //if there is a piece and then a blank to either side
			else if (col >= 2 && col <= 4 && board[row][col - 1] == first && board[row][col + 1] == first && board[row][col - 2] == 0 && board[row][col + 2] == first){
				if (first == this->p) hValue = twoPiecesBothEnds; //saves that the ai has the advantage
				else hValue = -twoPiecesBothEnds; //the player has the advantage
			}
			else { //otherwise there are two other pieces
				if (first == this->p) hValue = twoOtherPieces; //saves if it is the ai that will win
				else hValue = -twoOtherPieces; //saves if it is the player who will win
			}
		}
		else if (inRow == 1) { //if there is 1 in a row
			if (col <= 5 && board[row][col + 1] == first){ //if  it goes to the right
				if ((col <= 3 && board[row][col + 2] == 0 && board[row][col + 3] == first) //if there is piece, blank, piece to the right
					|| (col >= 2 && board[row][col - 1] == 0 && board[row][col - 2] == first)) {//if there is a piece to the right and blank, piece to the left
					if (first == this->p) hValue = twoOtherPieces; //ai has advantage
					else hValue = -twoOtherPieces; //player has advantage
				}
				else {
					if (first == this->p) hValue = oneOtherPiece; //saves if it is the ai that has the advantage
					else hValue = -oneOtherPiece; //the player has the advantage
				}
			}
			else { //if it goes to the left
				if ((col <= 4 && board[row][col + 1] == 0 && board[row][col + 2] == first) //if there is a piece to the left and blank, piece to the right
					|| (col >= 3 && board[row][col-2] == 0 && board[row][col-3] == first)){ //if there is piece, blank, piece to the left
					if (first == this->p) hValue = twoOtherPieces; //ai has advantage
					else hValue = -twoOtherPieces; //player has advantage
				}
				else {
					if (first == this->p) hValue = oneOtherPiece; //saves if it is the ai that has the advantage
					else hValue = -oneOtherPiece; //the player has the advantage
				}
			}
		}
		else { //if there are 0 in a row
			if ((col >= 3 && board[row][col - 1] == 0 && board[row][col - 2] == first && board[row][col - 3] == first) //if there is blank piece piece in either direction
				|| (col <= 3 && board[row][col + 1] == 0 && board[row][col + 2] == first && board[row][col + 3] == first)) {
				if (first == this->p) hValue = twoOtherPieces; //ai has advantage
				else hValue = -twoOtherPieces; //player has advantage
			}
			else if ((col >= 2 && board[row][col - 1] == 0 && board[row][col - 2] == first) //left space piece
				|| (col >= 3 && board[row][col - 1] == 0 && board[row][col-2] == 0 && board[row][col-3] == first) //left space space piece
				|| (col <= 4 && board[row][col+1] == 0 && board[row][col+2] == first) //right space piece
				|| (col <= 3 && board[row][col+1] == 0 && board[row][col+2] == 0 && board[row][col+3] == first)){ //right space space piece
				if (first == this->p) hValue = oneOtherPiece; //saves if it is the ai that has the advantage
				else hValue = -oneOtherPiece; //the player has the advantage
			}
			else hValue = useless; //otherwise the space is useless
		}
	}
	if (count2 != -1) { //if count2 is not negative
		if (hValue + hValue2 >= 0) { //if the sum of the two is positive or 0
			hValue = abs(hValue) + abs(hValue2); //hValue is set to the positive of the absolute values added together
		}
		else { //if they are negative
			hValue = -abs(hValue) - abs(hValue2); //it is set to the negative sum
		}
	}

	//analyze the up right diagonal
	first = 0; //resets the first and the pieces to 0
	short first2 = 0;
	int urValue2 = 0;
	urValue = 0;
	pieces = 0;
	pieces2 = 0;
	count = 0;
	count2 = 0;
	if (urCount < 4) { //if the diagonal is less than 4 spaces it is useless
		urValue = useless;
	}
	else {
		for (int i = col - 1; i >= 0 && i > col - 4; i--){ //for each space in the diagonal going left up to 3 spaces
			if (first == 0) {
				if (rUp[i] == 0) count++; //if the space is empty increases count
				else if (rUp[i] == -1) break; //breaks if the space is off the board
				else {
					pieces = 1;//sets pieces to 1
					first = rUp[i]; //saves the first
					count++;//increases count
				}
			}
			else {
				if (rUp[i] == first){ //if the space is the same as first
					count++; //increases count and the pieces
					pieces++;
				}
				else if (rUp[i] == 0) count++; //if the space is 0 increases count
				else break; //otherwise it breaks
			}
		}
		for (int i = col + 1; i < 7 && i < col + 4; i++){ //for the next 3 spaces diagonally to the left
			if (first2 == 0){
				if (rUp[i] == 0) count2++; //if the space is empty increases count
				else if (rUp[i] == -1) break; //breaks if it goes off the board
				else{
					pieces2 = 1; //sets pieces2
					first2 = rUp[i]; //saves the first piece
					count2++;
				}
			}
			else {
				if (rUp[i] == first2) { //if the space is the same as first2
					count2++; //increases the count an pieces
					pieces2++;
				}
				else if (rUp[i] == 0) count2++; //increases count if it is 0
				else break; //otherwise it breaks
			}
		}
		if (first == 0 && first2 == 0){ //if they are both 0
			urValue = emptyRow;//the row is empty
			count2 = -2; //-2 signifies it is done
			pieces2 = -2;
			first2 = -2;
		}
		else if (first != 0 && (first == first2 || first2 == 0)){ //if the firsts are the same or if first2 is 0 they are combined 
			first2 = -1; //first 2 is set to -1 to signal it is not used
			count += count2 + 1; //count is increased by count2
			count2 = -1;
			pieces += pieces2; //pieces is increased
			pieces2 = -1;
		}
		else if (first == 0) { //if first is 0
			first = first2; //it is set to first2
			count += count2 + 1; //count in increased
			pieces = pieces2; //pieces is increased
			first2 = -1; //set to negative 
			count2 = -1; 
			pieces2 = -1; 
		}
		else { //otherwise have to count spaces backwards
			for (int i = col; i >= 0; i--){ //counts backwards for count2
				if (rUp[i] == 0) count2++; //count2 is increased
				else break;
			}
			for (int i = col; i < 7; i++){ //counts for count
				if (rUp[i] == 0) count++; //count is increased
				else break;
			}
			if (count < 4 && count2 < 4){ //if both counts are less than 4
				count2 = -2; //signal that it is done
				pieces2 = -2;
				first2 = -2;
				urValue = useless; //the diagonal is useless
			}
			else if (count < 4) { //if count is less than 4
				first = first2; //first is set to first2
				count = count2; //count is set
				pieces = pieces2; //pieces is set
				first2 = -1;
				pieces2 = -1;
				count2 = -1;
			}
			if (count2 < 4) {//if count2 is less than 4
				count2 = -1; //it is deleted
				pieces2 = -1;
				first2 = -1;			
			}
			if (pieces2 > 0) { //if there is a pieces2 analyse it
				inRow = 0;
				for (int i = col + 1; i < 7 && i < col + 4; i++){
					if (rUp[i] == first2) inRow++; //increases the row
					else break; //otherwise breaks
				}
				if (inRow >= 3){ //if inRow is 3
					if (first2 == p) urValue = threeOtherPieces; //ai has advantage
					else urValue = -threeOtherPieces;//plays has advantage
					if (!complete) return urValue; //returns immediately
				}
				else if (inRow == 2) { //if inRow is 2
					if (col <= 3 && rUp[col + 3] == 0) { //if there is piece, piece, blank
						if (first2 == p) urValue = twoPiecesBothEnds; //ai has advantage
						else urValue = -twoPiecesBothEnds;//plays has advantage
					}
					else{ //if there is piece, piece, end
						if (first2 == p) urValue = twoOtherPieces; //ai has advantage
						else urValue = -twoOtherPieces;//plays has advantage
					}
				}
				else if (inRow == 1) { //if inRow is 1
					if (col <= 3 && rUp[col + 2] == 0 && rUp[col + 3] == first2){ //if there is piece blank piece
						if (first2 == p) urValue = twoOtherPieces; //ai has advantage
						else urValue = -twoOtherPieces;//plays has advantage
					}
					else { //if there is only the one piece to the right
						if (first2 == p) urValue = oneOtherPiece; //ai has advantage
						else urValue = -oneOtherPiece; //plays has advantage
					}
				}
				else { //if inRow is 0
					if (col <= 3 && rUp[col + 2] == first2 && rUp[col + 3] == first2) { //if there is blank piece piece
						if (first2 == p) urValue = twoOtherPieces; //ai has advantage
						else urValue = -twoOtherPieces; //plays has advantage
					}
					else { //otherwise there is only 1 
						if (first2 == p) urValue = oneOtherPiece; //ai has advantage
						else urValue = -oneOtherPiece; //plays has advantage
					}
				}
			}
		}
		if (count2 != -2) { //if count2 is not -2 analyse st00fs
			inRow = 0; //resets inRow
			for (int i = col - 1; i >= 0 && i > col - 4; i--){ //counts stuff in a row
				if (rUp[i] == first) inRow++; //increases inRow
				else break; 
			}
			for (int i = col + 1; i < 7 && i < col + 4; i++){ //counts going to the right
				if (rUp[i] == first) inRow++;// increases inRo
				else break;
			}
			if (pieces == 0) urValue2 = emptyRow; //the row is empty
			else if (inRow >= 3){ //if inRow is 3 or more
				if (first == p) urValue2 = threeOtherPieces; //ai has advantage
				else urValue2 = -threeOtherPieces; //player has advantage
				if (!complete) return urValue2; //returns immediately
			}
			else if (inRow == 2){ //if inRow is 2
				if ((col >= 3 && rUp[col - 1] == first && rUp[col - 2] == first && rUp[col - 3] == 0) //if there is piece, piece, space left
					|| (col <= 3 && rUp[col + 1] == first && rUp[col + 2] == first && rUp[col + 3] == 0) //piece, piece, space right
					|| (col <= 4 && col >= 2 && rUp[col - 1] == first && rUp[col + 1] == first && rUp[col - 2] == 0 && rUp[col + 2] == 0)){ //piece space to either side
					if (first == p) urValue2 = twoPiecesBothEnds; //ai has advantage
					else urValue2 = -twoPiecesBothEnds; //player has advantag
				}
				else {
					if (first == p) urValue2 = twoOtherPieces; //ai has advantage
					else urValue2 = -twoOtherPieces; //player has advantage
				}
			}
			else if (inRow == 1) { //if inRow is 1
				if ((col >= 3 && rUp[col-1] == first && rUp[col-2] == 0 && rUp[col-3] == first) //if there is piece blank piece to either side
					|| (col <= 3 && rUp[col+1] == first && rUp[col+2] == 0 && rUp[col+3] == first)
					|| (col >= 1 && col <= 4 && rUp[col-1] == first && rUp[col+1] == 0 && rUp[col+2] == first) //if there is a piece on one side and blank piece on the other side
					|| (col >= 2 && col <= 5 && rUp[col+1] == first && rUp[col-1] == 0 && rUp[col-2] == first)){
					if (first == p) urValue2 = twoOtherPieces; //ai has advantage
					else urValue2 = -twoOtherPieces; //player has advantage
				}
				else {
					if (first == p) urValue2 = oneOtherPiece; //ai has advantage
					else urValue2 = -oneOtherPiece; //player has advantage
				}
			}
			else { //otherwise inRow is 0
				if ((col >= 3 && rUp[col-1] == 0 && rUp[col-2] == first && rUp[col-3] == first) //if there is blank piece piece to either side
					|| (col <= 3 && rUp[col+1] == 0 && rUp[col+2] == first && rUp[col+3] == first)){
					if (first == p) urValue2 = twoOtherPieces; //ai has advantage
					else urValue2 = -twoOtherPieces; //player has advantage
				}
				else { //otherwise there is only 1 piece
					if (first == p) urValue2 = oneOtherPiece; //ai has advantage
					else urValue2 = -oneOtherPiece; //player has advantage
				}
			}
		}
	}
	if (urValue + urValue2 >= 0) { //if the sum of the two is positive or 0
		urValue = abs(urValue) + abs(urValue2); //hValue is set to the positive of the absolute values added together
	}
	else { //if they are negative
		urValue = -abs(urValue) - abs(urValue2); //it is set to the negative sum
	}

	//analyze the down right diagonal
	first = 0; //resets the first and the pieces to 0
	first2 = 0;
	int drValue2 = 0;
	drValue = 0;
	pieces = 0;
	pieces2 = 0;
	count = 0;
	count2 = 0;
	if (drCount < 4) { //if the diagonal is less than 4 spaces it is useless
		drValue = useless;
	}
	else {
		for (int i = col - 1; i >= 0 && i > col - 4; i--){ //for each space in the diagonal going left up to 3 spaces
			if (first == 0) {
				if (rDown[i] == 0) count++; //if the space is empty increases count
				else if (rDown[i] == -1) break; //breaks if the space is off the board
				else {
					pieces = 1;//sets pieces to 1
					first = rDown[i]; //saves the first
					count++;//increases count
				}
			}
			else {
				if (rDown[i] == first){ //if the space is the same as first
					count++; //increases count and the pieces
					pieces++;
				}
				else if (rDown[i] == 0) count++; //if the space is 0 increases count
				else break; //otherwise it breaks
			}
		}
		for (int i = col + 1; i < 7 && i < col + 4; i++){ //for the next 3 spaces diagonally to the left
			if (first2 == 0){
				if (rDown[i] == 0) count2++; //if the space is empty increases count
				else if (rDown[i] == -1) break; //breaks if it goes off the board
				else{
					pieces2 = 1; //sets pieces2
					first2 = rDown[i]; //saves the first piece
					count2++;
				}
			}
			else {
				if (rDown[i] == first2) { //if the space is the same as first2
					count2++; //increases the count an pieces
					pieces2++;
				}
				else if (rDown[i] == 0) count2++; //increases count if it is 0
				else break; //otherwise it breaks
			}
		}
		if (first == 0 && first2 == 0){ //if they are both 0
			drValue = emptyRow;//the row is empty
			count2 = -2; //-2 signifies it is done
			pieces2 = -2;
			first2 = -2;
		}
		else if (first != 0 && (first == first2 || first2 == 0)){ //if the firsts are the same or if first2 is 0 they are combined 
			first2 = -1; //first 2 is set to -1 to signal it is not used
			count += count2 + 1; //count is increased by count2
			count2 = -1;
			pieces += pieces2; //pieces is increased
			pieces2 = -1;
		}
		else if (first == 0) { //if first is 0
			first = first2; //it is set to first2
			count += count2 + 1; //count in increased
			pieces = pieces2; //pieces is increased
			first2 = -1; //set to negative 
			count2 = -1;
			pieces2 = -1;
		}
		else { //otherwise have to count spaces backwards
			for (int i = col; i >= 0; i--){ //counts backwards for count2
				if (rDown[i] == 0) count2++; //count2 is increased
				else break;
			}
			for (int i = col; i < 7; i++){ //counts for count
				if (rDown[i] == 0) count++; //count is increased
				else break;
			}
			if (count < 4 && count2 < 4){ //if both counts are less than 4
				count2 = -2; //signal that it is done
				pieces2 = -2;
				first2 = -2;
				drValue = useless; //the diagonal is useless
			}
			else if (count < 4) { //if count is less than 4
				first = first2; //first is set to first2
				count = count2; //count is set
				pieces = pieces2; //pieces is set
				first2 = -1;
				pieces2 = -1;
				count2 = -1;
			}
			if (count2 < 4) {//if count2 is less than 4
				count2 = -1; //it is deleted
				pieces2 = -1;
				first2 = -1;
			}
			if (pieces2 > 0) { //if there is a pieces2 analyse it
				inRow = 0;
				for (int i = col + 1; i < 7 && i < col + 4; i++){
					if (rDown[i] == first2) inRow++; //increases the row
					else break; //otherwise breaks
				}
				if (inRow >= 3){ //if inRow is 3
					if (first2 == p) drValue = threeOtherPieces; //ai has advantage
					else drValue = -threeOtherPieces;//plays has advantage
					if (!complete) return drValue; //returns immediately
				}
				else if (inRow == 2) { //if inRow is 2
					if (col <= 3 && rDown[col + 3] == 0) { //if there is piece, piece, blank
						if (first2 == p) drValue = twoPiecesBothEnds; //ai has advantage
						else drValue = -twoPiecesBothEnds;//plays has advantage
					}
					else{ //if there is piece, piece, end
						if (first2 == p) drValue = twoOtherPieces; //ai has advantage
						else drValue = -twoOtherPieces;//plays has advantage
					}
				}
				else if (inRow == 1) { //if inRow is 1
					if (col <= 3 && rDown[col + 2] == 0 && rDown[col + 3] == first2){ //if there is piece blank piece
						if (first2 == p) drValue = twoOtherPieces; //ai has advantage
						else drValue = -twoOtherPieces;//plays has advantage
					}
					else { //if there is only the one piece to the right
						if (first2 == p) drValue = oneOtherPiece; //ai has advantage
						else drValue = -oneOtherPiece; //plays has advantage
					}
				}
				else { //if inRow is 0
					if (col <= 3 && rDown[col + 2] == first2 && rDown[col + 3] == first2) { //if there is blank piece piece
						if (first2 == p) drValue = twoOtherPieces; //ai has advantage
						else drValue = -twoOtherPieces; //plays has advantage
					}
					else { //otherwise there is only 1 
						if (first2 == p) drValue = oneOtherPiece; //ai has advantage
						else drValue = -oneOtherPiece; //plays has advantage
					}
				}
			}
		}
		if (count2 != -2) { //if count2 is not -2 analyse st00fs
			inRow = 0; //resets inRow
			for (int i = col - 1; i >= 0 && i > col - 4; i--){ //counts stuff in a row
				if (rDown[i] == first) inRow++; //increases inRow
				else break;
			}
			for (int i = col + 1; i < 7 && i < col + 4; i++){ //counts going to the right
				if (rDown[i] == first) inRow++;// increases inRo
				else break;
			}

			if (pieces == 0) drValue2 = emptyRow; //the row is empty
			else if (inRow >= 3){ //if inRow is 3 or more
				if (first == p) drValue2 = threeOtherPieces; //ai has advantage
				else drValue2 = -threeOtherPieces; //player has advantage
				if (!complete) return drValue2; //returns immediately
			}
			else if (inRow == 2){ //if inRow is 2
				if ((col >= 3 && rDown[col - 1] == first && rDown[col - 2] == first && rDown[col - 3] == 0) //if there is piece, piece, space left
					|| (col <= 3 && rDown[col + 1] == first && rDown[col + 2] == first && rDown[col + 3] == 0) //piece, piece, space right
					|| (col <= 4 && col >= 2 && rDown[col - 1] == first && rDown[col + 1] == first && rDown[col - 2] == 0 && rDown[col + 2] == 0)){ //piece space to either side
					if (first == p) drValue2 = twoPiecesBothEnds; //ai has advantage
					else drValue2 = -twoPiecesBothEnds; //player has advantag
				}
				else {
					if (first == p) drValue2 = twoOtherPieces; //ai has advantage
					else drValue2 = -twoOtherPieces; //player has advantage
				}
			}
			else if (inRow == 1) { //if inRow is 1
				if ((col >= 3 && rDown[col - 1] == first && rDown[col - 2] == 0 && rDown[col - 3] == first) //if there is piece blank piece to either side
					|| (col <= 3 && rDown[col + 1] == first && rDown[col + 2] == 0 && rDown[col + 3] == first)
					|| (col >= 1 && col <= 4 && rDown[col - 1] == first && rDown[col + 1] == 0 && rDown[col + 2] == first) //if there is a piece on one side and blank piece on the other side
					|| (col >= 2 && col <= 5 && rDown[col + 1] == first && rDown[col - 1] == 0 && rDown[col - 2] == first)){
					if (first == p) drValue2 = twoOtherPieces; //ai has advantage
					else drValue2 = -twoOtherPieces; //player has advantage
				}
				else {
					if (first == p) drValue2 = oneOtherPiece; //ai has advantage
					else drValue2 = -oneOtherPiece; //player has advantage
				}
			}
			else { //otherwise inRow is 0
				if ((col >= 3 && rDown[col - 1] == 0 && rDown[col - 2] == first && rDown[col - 3] == first) //if there is blank piece piece to either side
					|| (col <= 3 && rDown[col + 1] == 0 && rDown[col + 2] == first && rDown[col + 3] == first)){
					if (first == p) drValue2 = twoOtherPieces; //ai has advantage
					else drValue2 = -twoOtherPieces; //player has advantage
				}
				else { //otherwise there is only 1 piece
					if (first == p) drValue2 = oneOtherPiece; //ai has advantage
					else drValue2 = -oneOtherPiece; //player has advantage
				}
			}
		}
	}
	if (drValue + drValue2 >= 0) { //if the sum of the two is positive or 0
		drValue = abs(drValue) + abs(drValue2); //hValue is set to the positive of the absolute values added together
	}
	else { //if they are negative
		drValue = -abs(drValue) - abs(drValue2); //it is set to the negative sum
	}

	//returns the combined value of the position
	if ((hValue >= 2 * threeOtherPieces || drValue >= 2 * threeOtherPieces || urValue >= 2 * threeOtherPieces) //if any of the directions will win for both players
		|| ((hValue >= threeOtherPieces || drValue >= threeOtherPieces || urValue >= threeOtherPieces || vValue >= threeOtherPieces) //of if any of them will win for one player
		&& (hValue <= -threeOtherPieces || drValue <= -threeOtherPieces || urValue <= -threeOtherPieces || vValue <= -threeOtherPieces))){ //and and other will win for the other player
		if (vValue + hValue + drValue + urValue >= 0){ //if the total value is positive
			return bothPlayersWin; //returns positive both players win
		}
		else { //if the sum is negative
			return -bothPlayersWin; //returns that both players win and it is better for the other player
		}
	}
	else if (vValue + hValue + drValue + urValue >= 0){ //if the total value is positive
		return abs(vValue) + abs(hValue) + abs(drValue) + abs(urValue); //returns the positive sum
	}
	else { //if the sum is negative
		return -abs(vValue) - abs(hValue) - abs(drValue) - abs(urValue); //returns the negative sum
	}
}
int FakeGame::emptySpot(int col) { //returns the bottom empty space in a given column (-1 = no empty space)
	for (int row = 0; row <= 6; row++){
		if (this->board[row][col] == 0)	return row; //returns the first empty row from the bottom
	}
	return -1; //returns -1 if there are no empty spaces
}
void FakeGame::fakeMove(int col, int p){ //function to make a move on a fake board
	for (int row = 0; row < 6; row++){ //from the bottom up of the column
		if (this->board[row][col] == 0) { //if the space is free
			this->board[row][col] = (p <= 1 ? 1 : 2); //sets it to the playerplayer
			break; //exits the loop
		}
	}
}
void FakeGame::undoMove(int col){ //function to remove the top piece from the board
	for (int row = 5; row >= 0; row--){ //starting at the top row going down
		if (this->board[row][col] != 0) { //when it gets to a non 0 piece
			this->board[row][col] = 0; //sets it to 0
			return; //ends the function
		}
	}
}
int FakeGame::analyseCol(ColVal &colVal, int col, short depth = colDepth, int row = -1){ //analyses the value of a column
	if (row == -1) row = this->emptySpot(col); //finds the bottom empty spot of the row 
	if (row == -1) {
		colVal = cantPlay; 
		return 0; //returns 0 if can't play in the column
	}
	int val = analysePosition(col, row, true); //analyses the position
	if (abs(val) >= bothPlayersWin) colVal = winBlock; //saves if both players can win in that spot
	else if (val >= threeOtherPieces) colVal = winNow; //saves if that column could win
	else if (val <= -threeOtherPieces) colVal = blockNow; //saves if the column needs blocking
	else if (val >= twoPiecesBothEnds) colVal = useful; //saves if the spot is useful
	else if (val <= -twoPiecesBothEnds) colVal = dangerous; //saves if the spot is dangerous
	else colVal = neutral; //saves if the column is basically neutral
	if (depth > 1 && row < 5) { //if there is more searching to do
		ColVal aCol;
		analyseCol(aCol, col, depth - 1, row + 1); //analyses the row from the position above
		if (colVal == winBlock); //if the current spot can win for either player
		else if (colVal == blockNow); //if the current spot has to be blocked it has to be blocked
		else if (colVal == winNow) { //if the current spot can win
			if (aCol == winNow || aCol == partOfWin || aCol == winBlock){ //if the spot above can also win
				colVal = partOfWin; //the spot can win and so can the one above it
			} //otherwise the spot will win, what's above doesnt matter
		}
		else if (aCol == winBlock) colVal = wbAbove; //saves if both players can win above
		else if (aCol == winNow) colVal = winAbove; //saves if the ai can win above
		else if (aCol == blockNow) colVal = doNotPlay; //saves if the oponent can win above
		else if (aCol == partOfWin) colVal = willWin1; //saves if there is a fork starting above
		else if (aCol == willWin1) colVal = willWin2; //saves if there is a fork higher up in the column
		else if (aCol == willWin2) colVal = willWin2; //saves if there is a fork higher up in the column
		else if (aCol == useful) colVal = enablesBlock; //saves if there is a potentially useful spot above
		else if (aCol == dangerous) colVal = enablesMove; //saves if the spot above may be useful to the enemy
		else if (aCol == neutral 
			|| aCol == enablesBlock
			|| aCol == enablesMove
			|| aCol == winAbove
			|| aCol == doNotPlay
			|| aCol == wbAbove  
			|| aCol == cantPlay); //if the spot above is insignificant the current space is passed back instead
	}
	return val; //returns the value of the current board position
}
int FakeGame::getNoOfCols(){ //returns the number of columns that arent full
	int count = 0;
	for (int col = 0; col < 7; col++){
		if (emptySpot(col) != -1) count++; //if the column is not full increases the count
	}
	return count;
}
int FakeGame::easyAiMove(){ //function to make an easy ai move
	int bestCol = -1; //keeps track of the best move so far
	int bestVal = 0; //the value of the best move so far
	for (int col = 0; col < 7; col++) { //for each column
		int row = emptySpot(col);
		if (row != -1){ //if there is a space in the column
			int val = analysePosition(col, row, true); //gets the column value
			if (col == 3) val *= centerModifier; //adds a multiplier to add center bias
			else if (col == 2 || col == 4) val *= oneOutModifier; 
			else if (col == 1 || col == 5) val *= twoOutModifier;
			else val *= threeOutModifier;
			if (val >= threeOtherPieces){ //if the value will complete a three in a row
				return col; //returns the column immediately
			}
			else if (abs(val) > abs(bestVal) || bestCol == -1) {
				bestCol = col; //new best column is saved 
				bestVal = val;
			}
			else if (abs(val) == abs(bestVal) && (val < bestVal || rand() % 2)){ 
				bestCol = col; //new best column is saved 
				bestVal = val;
			}
		}
	}
	if (abs(bestVal) >= threeOtherPieces && rand()%2) { //1/2 chance of playing if there is a winning spot
		return bestCol; //returns the best column
	}
	else {
		int c = rand() % getNoOfCols(); //finds the number of empty columns
		for (int col = 0; col < 7; col++) {
			if (emptySpot(col) != -1) {
				if (c == 0) return col; //returns the first empty column
				c--;
			}
		}
		return rand() % 7;
	}
}
int FakeGame::mediumAiMove(){ //function to make a medium ai move
	int bestCol = -1; //keeps track of the best move so far
	int bestVal = 0; //the value of the best move so far
	for (int col = 0; col < 7; col++) { //for each column
		int row = emptySpot(col);
		if (row != -1){ //if there is a space in the column
			int val = analysePosition(col, row, true); //gets the column value
			if (col == 3) val *= centerModifier; //adds a multiplier to add center bias
			else if (col == 2 || col == 4) val *= oneOutModifier;
			else if (col == 1 || col == 5) val *= twoOutModifier;
			else val *= threeOutModifier;
			if (val >= threeOtherPieces){ //if the value will complete a three in a row
				return col; //returns the column immediately
			}
			else if (abs(val) > abs(bestVal) || bestCol == -1) { //if the new value has a higher magnitude than the old one
				bestCol = col; //new best column is saved 
				bestVal = val;
			}
			else if (abs(val) == abs(bestVal) && bestVal < threeOtherPieces && (val < bestVal || rand() % 2)){
				bestCol = col; //new best column is saved 
				bestVal = val;
			}
		}
	}
	if (abs(bestVal) >= threeOtherPieces || !(rand() % 10)) { //plays in winning spots or 50% chance of playing in the best spot
		return bestCol; //returns the best column
	}
	else {
		int c = rand() % getNoOfCols(); //finds the number of empty columns
		for (int col = 0; col < 7; col++) {
			if (emptySpot(col) != -1) {
				if (c == 0) return col; //returns the first empty column
				c--;
			}
		}
	}
	//return bestCol; //returns the best column
}
int FakeGame::aiMove(ColVal& val, short depth = recursionDepth){
	int values[7] = {};
	ColVal colVal[7] = {};
	int bestMove = 0;
	bool unsure[7] = {};
	bool recurse = false;

	//finds the values of the individual columns
	for (int col = 0; col < 7; col++){
		values[col] = analyseCol(colVal[col], col, colDepth); //gets the values of each column and the values of the bottom space in each
		if (col == 3) values[col] *= centerModifier; //adds a multiplier to add center bias
		else if (col == 2 || col == 4) values[col] *= oneOutModifier;
		else if (col == 1 || col == 5) values[col] *= twoOutModifier;
		else values[col] *= threeOutModifier;
		if (values[col] >= threeOtherPieces || abs(values[col]) >= bothPlayersWin){ //if the value will complete a three in a row
			bestMove = col;
			val = (values[col] >= threeOtherPieces ? winNow : winBlock);
			return bestMove; //returns the column immediately
		}
	}

	//checks each column to find the best
	for (int col = 0; col < 7; col++){

		if (colVal[col] >= cantPlay) unsure[col] = false; //if they cant play in the column it can't be better
		else if (colVal[col] >= doNotPlay) { //if both the current and best are really bad picks which one is better
			unsure[col] = false;
			if ((colVal[bestMove] >= doNotPlay && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] >= cantPlay) bestMove = col;
		}
		else if (colVal[col] >= willWin1) { //if the move is not obviously bad or good
			unsure[col] = true; 
			if (colVal[bestMove] < blockNow); //if the best move is obviously good does nothing
			else if (colVal[bestMove] > winAbove) { //if the best move so far was a bad move
				bestMove = col; //saves the best move and doesnt look ahead yet
			}
			else { //if the previous best move was also not obvious
				if (depth > 1){
					recurse = true; //will check ahead recursively
				}
				else { //otherwise just picks the best move
					if (colVal[col] >= winAbove) { //if there is a win above and the previous best is worse
						if ((colVal[bestMove] >= winAbove && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > winAbove) bestMove = col;
					}
					else if (colVal[col] >= enablesBlock){ //if the spot above could be useful to either player but it is better than the previous best
						if ((colVal[bestMove] >= enablesBlock && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > enablesMove) bestMove = col;
					}
					else if (colVal[col] >= neutral) { //if the spot is neutral and better than the previous best
						if ((colVal[bestMove] >= neutral && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > neutral) bestMove = col;
					}
					else if (colVal[col] >= useful) { //if the spot is useful to either player but better than the previous best
						if ((colVal[bestMove] >= useful && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > dangerous) bestMove = col;
					}
					else if (colVal[col] >= willWin1) { //if the spot will win eventually and is better than the previous best
						if (((colVal[col] == colVal[bestMove]) //if they are the same and one is better
							&& abs(values[col]) > abs(values[bestMove]))
							|| colVal[bestMove] > colVal[col]) bestMove = col; //or if it is just better
					}
				}
			}
		}
		else if (colVal[col] >= blockNow) { //if the move has to be blocked now
			unsure[col] = false;
			recurse = false;
			if ((colVal[bestMove] >= blockNow && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > blockNow) bestMove = col;
		}
		else /*(colVal[col] >= winBlock)*/{ //if the move will win now picks the best one
			unsure[col] = false;
			recurse = false;
			if ((colVal[bestMove] >= winBlock && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > winNow) bestMove = col;
		}
	}
	if (recurse){ //if it is unsure about the best move
		for (short col = 0; col < 7; col++) {//for each move being considered
			if (unsure[col]) { //if the move is not obviously bad or good
				fakeMove(col, this->p); //makes a fake move
				ColVal worstCol, tempVal;
				aiMove(worstCol, depth - 1); //gets the value of the first column
				for (short col2 = 1; col2 < 7; col2++) { //for each possible player move
					fakeMove(col2, (this->p == 1 ? 2 : 1)); //make the player move
					aiMove(tempVal, depth - 1); //gets the next best move					
					if (tempVal > worstCol && tempVal != cantPlay) { //if the value from the next move is worse than the worst so far
						worstCol = tempVal; //that is saved
					}
					undoMove(col2); //undoes the fake player move
				}
				undoMove(col); //undoes the fake ai move

				if (worstCol <= willWin2 && worstCol != blockNow){ //if the worst outcome will win eventually
					colVal[col] = willWin1; //saves that the column will win
				}
				else;
				if (colVal[col] == colVal[bestMove]) { //if the column value is the same as the worse column
					if (abs(values[col]) > abs(values[col])) bestMove = col; //if the current position has a higher value it is saved instead
				}
				else if (colVal[col] < colVal[bestMove]){ //if the column value is better than the best so far
					bestMove = col;
				}
			}
		}
		for (int col = 0; col < 7; col++){
			if (colVal[col] >= cantPlay); //if they cant play in the column it can't be better
			else if (colVal[col] >= doNotPlay) { //if both the current and best are really bad picks which one is better
				if ((colVal[bestMove] >= doNotPlay && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] >= cantPlay) bestMove = col;
			}
			else if (colVal[col] >= winAbove) { //if there is a win above and the previous best is worse
				if ((colVal[bestMove] >= winAbove && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > winAbove) bestMove = col;
			}
			else if (colVal[col] >= enablesBlock){ //if the spot above could be useful to either player but it is better than the previous best
				if ((colVal[bestMove] >= enablesBlock && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > enablesMove) bestMove = col;
			}
			else if (colVal[col] >= neutral) { //if the spot is neutral and better than the previous best
				if ((colVal[bestMove] >= neutral && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > neutral) bestMove = col;
			}
			else if (colVal[col] >= willWin1) { //if the spot will win eventually and is better than the previous best
				if (((colVal[col] == colVal[bestMove]) //if they are the same and one is better
					&& abs(values[col]) > abs(values[bestMove]))
					|| colVal[bestMove] > colVal[col]) bestMove = col; //or if it is just better
			}
			else if (colVal[col] >= blockNow) { //if the move has to be blocked now
				unsure[col] = false;
				recurse = false;
				if ((colVal[bestMove] >= blockNow && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > blockNow) bestMove = col;
			}
			else /*(colVal[col] >= winBlock)*/{ //if the move will win now picks the best one
				unsure[col] = false;
				recurse = false;
				if ((colVal[bestMove] >= winBlock && abs(values[col]) > abs(values[bestMove])) || colVal[bestMove] > winNow) bestMove = col;
			}
		}
	}

	val = colVal[bestMove];
	return bestMove; //returns the best move 
}
int FakeGame::hardAiMove() { //function to make a hard ai move
	ColVal val;
	return aiMove(val); //runs the aiMove function
}
