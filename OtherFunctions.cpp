//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

void clearScreen(int text, int background){ //function to clear the screen and set the background/text colours
	setCursorColour(text, background); //sets the colour and background (to defaults)
	system("cls"); //clears the screen
	setCursorPosition(); //sets the cursor back to the origin
	_flushall(); //clears the keyboard buffer
}
void setCursorColour(int text, int background){ //function to set cursor colour
	if (text > 15) text = 15; //makes sure the text colour is between 0 and 15
	else if (text < 0) text = 0;
	if (background > 15) background = 15; //makes sure the background colour is between 0 and 15
	else if (background < 0) background = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text + 16*background); //sets the cursor colour
}
void setCursorPosition(int x, int y) { //function to set the cursor position
	if (x < 0) x = 0; //makes sure x is between 0 and 79
	else if (x > 79) x = 79;
	if (y < 0) y = 0; //makes sure y is at least 0 and less than 300
	if (y > 299) y = 299;
	COORD p = { x, y }; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p); //sets the console position
}
bool isInteger(string num){ //function to check if a string is an integer
	if (num == "") return false; //if the string has no characters it cant be an integer
	for (size_t i = 0; i < num.size(); i++){ //check each character
		switch (num[i]){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			break; //if the character is a number nothing happens
		default: return false; //if the character is any other character 0 is returned (not an integer)
		}
	}
	return true; //returns true if all of the characters are integers
}
