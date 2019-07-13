//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

Menu::Menu(vector<MenuOption>& options, string title, string bottomText, int align){ //constructor for menu class
	this->options = options; //copies the options into the data members
	this->selection = 0; //sets the selection to 0 (first option)
	this->selMax = options.size() - 1; //sets the max selection to the number of options -1
	this->title = title.substr(0, 76); //copies the title into the data members
	this->alignment = align;
	this->bottomText = bottomText; //saves the bottom text
	if (this->bottomText != ""){ //if there is a bottom text
		string tempBottomText = this->bottomText; //the bottom text is saved temporarily
		while (tempBottomText.find(".") != string::npos){ //while the temporary bottom text still has a period
			this->bottomTextLines.push_back(tempBottomText.substr(0, tempBottomText.find(".")+1)); //creates a new line of the bottom text
			tempBottomText += "  "; //some spaces are added to the end of the temporary bottom text
			tempBottomText = tempBottomText.substr(tempBottomText.find(".") + 2, tempBottomText.size()); //bottom text temp is decreased
		}
	}
}
void Menu::setTitle(string title){ //function to change the title
	this->title = title;
}
void Menu::upSelect(){ //moves the selection up 1
	if (this->selection == this->selMin) this->selection = this->selMax; //if the selection is already at the minimum it is set to the maximum
	else this->selection -= 1; //otherwise it is decreased by 1
	this->displayMenu(); //updates the screen
}
void Menu::downSelect(){ //moves the selection down 1
	if (this->selection == this->selMax) this->selection = this->selMin; //if the selection is already at the max it is set to the minimum
	else this->selection += 1; //otherwise it is increased by 1
	this->displayMenu(); //updates the screen
}
void Menu::displayMenu(bool first){ //displays the menu
	if (first){ //if it is the first time the menu is being displayed
		clearScreen(); //clears the screen
		setCursorPosition((76 - this->title.length()) / 2, 1);
		for (size_t i = 0; i < this->title.length() + 4; i++){
			cout << "-"; //outputs the top border of the menu title
		}
		setCursorPosition((76 - this->title.length()) / 2, 2);
		cout << "| " << this->title << " |"; //outputs the title of the menu
		setCursorPosition((76 - this->title.length()) / 2, 3);
		for (size_t i = 0; i < this->title.length() + 4; i++){
			cout << "-"; //outputs the bottom border of the menu title
		}
		if (this->bottomTextLines.size() > 0){ //if there is bottom text
			int lineY = 7 + 2 * this->selMax; //sets the starting line
			if (lineY < (24 - bottomTextLines.size())) lineY = 24 - bottomTextLines.size(); //puts the bottom text at the bottom of the screen or after the options

			for (size_t i = 0; i < bottomTextLines.size(); i++){ //for the number of lines
				int lineX;
				switch (this->alignment){
				case alignCenter: //if it is aligned to the center
					lineX = (80 - bottomTextLines[i].length()) / 2; //sets the x alignment to center the line
					break;
				case alignLeft: //if it is left aligned
					lineX = 19; //sets the x alignment to the default
					break;
				}
				setCursorColour(highlightColourText, highlightColourBack); //resets the colour
				setCursorPosition(lineX, lineY); //sets the cursor location
				cout << this->bottomTextLines[i]; //outputs the line
				lineY++;
			}
		}
	}
	for (int i = 0; i <= this->selMax; i++){ //for each option
		this->options[i].displayOption(5 + 2 * i, this->alignment, (selection == i ? 1 : 0)); //displays the options
	}
}
int Menu::getSelection(){ //returns the selection when the menu closes
	int keyInput;
	this->displayMenu(1); //shows the menu
	do {
		switch (keyInput = _getch()){ //gets a key from the keyboard
		case upKey: //if the up key is pressed
			this->upSelect(); //moves the selection up 1 
			displayMenu(); //refreshes the screen
			break;
		case downKey: //if the down key is pressed
			this->downSelect(); //move the selection down 1
			displayMenu(); //refreshes the screen
			break;
		case leftKey: //if the left key is pressed
			this->options[selection].decreasValue(); //changes the option value if possible
			displayMenu(); //refreshes the screen
			break;
		case rightKey: //if the right key is pressed
			this->options[selection].increaseValue(); //changes the value if possible
			displayMenu(); //refreshes the screen
			break;
		case escKey: //if escape is press
			this->selection = selMax; //the selection is set to the last option
			keyInput = enterKey; //the input is set to the enter key to signal exit
			break;
		default:; //any other key is ignored
		}
	} while (!(keyInput == enterKey || keyInput == spaceKey)); //exits when the enter or space key is pressed
	clearScreen(); //clears the screen
	return this->selection; //returns whatever was selected when enter is pressed
}
void Menu::updateOptions(vector<MenuOption>& options){ //updates the menu options
	this->options = options;
	this->selMax = options.size() - 1; //sets the max selection to the number of options -1
}
void Menu::changeMessage(string message){
	this->bottomText = message; //changes the bottom text message
	this->bottomTextLines.clear(); //clears the old vector
	if (this->bottomText != ""){ //if there is a bottom text
		string tempBottomText = this->bottomText; //the bottom text is saved temporarily
		while (tempBottomText.find(".") != string::npos){ //while the temporary bottom text still has a period
			this->bottomTextLines.push_back(tempBottomText.substr(0, tempBottomText.find(".") + 1)); //creates a new line of the bottom text
			tempBottomText += "  "; //some spaces are added to the end of the temporary bottom text
			tempBottomText = tempBottomText.substr(tempBottomText.find(".") + 2, tempBottomText.size()); //bottom text temp is decreased
		}
	}
}