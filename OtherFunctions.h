//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

void clearScreen(int text=15, int background=0); //function to clear the screen and set the background/text colours
void setCursorColour(int text=15, int background=0); //function to change the cursor colour
void setCursorPosition(int x=0, int y=0); //function to set the cursor position
bool isInteger(string num); //function to check if a string is an integer