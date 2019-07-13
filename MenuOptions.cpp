//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

MenuOption::MenuOption(string name){ //constructor for a regular menu option
	this->name = name; //saves the name and type
	this->type = regularMenuOption;
	this->valueMax = 0; //the max and min values are not necessary
	this->valueMin = 0;
	this->value = NULL; //the value to modify is NULL because there isnt one
}
MenuOption::MenuOption(string name, int type, int* value, int valueMin, int valueMax){ //constructor for special menu options
	this->name = name; //name and type are saved
	this->type = type;
	this->valueMax = valueMax; //saves the min and max values
	this->valueMin = valueMin;
	this->value = value; //saves the value
}
MenuOption::MenuOption(string name, int type, int* value, vector<string> values){ //constructor for special menu options with strings for each option
	this->name = name; //name and type are saved
	this->type = type;
	this->valueMax = values.size() - 1; //saves the min and max values
	this->valueMin = 0;
	this->value = value; //saves the value
	this->values = values; //saves the text values of each option
}
void MenuOption::initialize(string name){ //initializes a regular menu option
	this->name = name; //saves the name and type
	this->type = regularMenuOption;
	this->valueMax = 0; //the max and min values are not necessary
	this->valueMin = 0;
	this->value = NULL; //the value to modify is NULL because there isnt one
}
void MenuOption::initialize(string name, int type, int* value, int valueMin, int valueMax){ //initializes special menu options
	this->name = name; //name and type are saved
	this->type = type;
	this->valueMax = valueMax; //saves the min and max values
	this->valueMin = valueMin;
	this->value = value; //saves the value
}
void MenuOption::initialize(string name, int type, int* value, vector<string> values){ //initializes special menu options with strings for each option
	this->name = name; //name and type are saved
	this->type = type;
	this->valueMax = values.size() - 1; //saves the min and max values
	this->valueMin = 0;
	this->value = value; //saves the value
	this->values = values; //saves the text values of each option
}
void MenuOption::increaseValue(){ //function to increase the value
	if (this->type != regularMenuOption){ //if it is not a regular menu option
		if (*value == valueMax) *value = valueMin; //if the value is at the max it is set to the minumum
		else *value = *value + 1; //otherwise the value is increased
	}
}
void MenuOption::decreasValue(){ //function to decrease the value
	if (this->type != regularMenuOption){ //if its not a regular menu option
		if (*value == valueMin) *value = valueMax; //if the value is already at the minimum it is set to the maximum
		else *value = *value -1; //otherwise the value is decresed
	}
}
void MenuOption::displayOption(int y, int alignment, int selected){ //function to display a value
	int x;
	switch (alignment){
	case alignCenter:
		int length; //keep track of the length of the option
		switch (this->type){
		case numberMenuOption:
			length = this->name.length() + 9; //if it is a number option, the length is set to the length of the name + 8 character for the number
			break;
		case colourMenuOption:
			length = this->name.length() + 11; //if it is a colour option the length is set to +11 characters for the colour shower
			break;
		case textMenuOption:
			length = this->name.length() + 18; //if the number has a text option, the length is set to the length of the name + 15 for the option
			break;
		default: //regular option or any other type
			length = this->name.length() + 2; //if it is a regular menu option the length is set to the length of the name + 2
		}
		x = (80 - length) / 2;
		break;
	case alignLeft:
		x = 19;
	}
	setCursorPosition(x-3, y); //sets the cursor position
	if (selected) { //if the current option is selected
		cout << ">> "; //outputs the selector
		setCursorColour(highlightColourBack, highlightColourText); //inverts the colours
	}
	else {
		setCursorColour(highlightColourText, highlightColourBack); //resets to the default colours
		cout << "   "; //overwrites the cursor
	}
	cout << " " << this->name << " "; //outputs the selection 
	setCursorColour(highlightColourText, highlightColourBack); //resets the colours
	int length;
	switch (this->type) {
	case numberMenuOption:
		cout << " < " << value << " >"; //outputs the number if it is a number option
		break;
	case colourMenuOption:
		cout << " < "; //outputs the left arrow
		setCursorColour(highlightColourText, *this->value); //changes the colour to the colour value
		cout << "   "; //outputs a sample of the colour
		setCursorColour(highlightColourText, highlightColourBack); //resets the colours
		cout << " >"; //outputs the right arrow
		break;
	case textMenuOption:
		cout << " < " << this->values[*this->value]; //outputs the left arrow and the value
		length = this->values[*this->value].length(); 
		for (int i = length; i < 10; i++){ //makes sure there are at least 10 characters
			cout << " "; //fills ads extra spaces
		}
		cout << " >        "; //outputs the right arrow and some extra spaces
		break;
	default:; //doesnt output anything else for regular options
	}
}
void MenuOption::changeValues(vector<string> values){ //function to change the values of a menu option
	this->values = values; //saves the new values
	this->valueMax = values.size() - 1; //saves the min and max values
	this->valueMin = 0;
}