//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

class MenuOption{ //class for menu options
public:
	MenuOption(string name = ""); //constructor for regular menu options
	MenuOption(string name, int type, int* value, int valueMin = 1, int valueMax = 15); //constructor for special menu options. 1 and 15 max and min are default for colours
	MenuOption(string name, int type, int* value, vector<string> values); //constructor for special menu options with strings for each option
	void initialize(string name = ""); //initializes regular menu options
	void initialize(string name, int type, int* value, int valueMin = 0, int valueMax = 15); //initializes special menu options
	void initialize(string name, int type, int* value, vector<string> values); //initializes special menu options with strings for each option
	void increaseValue();
	void decreasValue();
	void displayOption(int y, int alignment = 0, int selected = 0);
	void changeValues(vector<string> values);
private:
	string name;
	int type;
	int valueMin;
	int valueMax;
	int* value;
	vector<string> values; 
};