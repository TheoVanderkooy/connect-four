//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"
#include"MenuOptions.h"

class Menu { //class for menus
public:
	Menu(vector<MenuOption>& options, string title, string bottomText = "", int align = 0);
	void setTitle(string title);
	void upSelect();
	void downSelect();
	void displayMenu(bool first = false);
	int getSelection();
	void updateOptions(vector<MenuOption>& options);
	void changeMessage(string message);
private:
	vector<MenuOption> options;
	string title;
	int selMax; 
	int const selMin = 0; //minimum selection is a constant (0)
	int selection;
	int alignment;
	string bottomText;
	vector<string> bottomTextLines;
};