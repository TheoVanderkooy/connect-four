//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

#include"ConnectFourIncludes.h"

void main(){
	setCursorPosition(35, 5);
	cout << "Loading..."; 
	srand(time(NULL)); //seeds the random number generator with the current system time
	SetConsoleTitle("Connect Four"); //sets the title of the console
	cout << fixed << setprecision(2); //sets the precision of doubles
	vector<string> statDifficulties(4); //different difficulties including vs players
	statDifficulties[0] = "   easy   ";
	statDifficulties[1] = "  medium  ";
	statDifficulties[2] = "   hard   ";
	statDifficulties[3] = "vs players";
	statDifficulties.shrink_to_fit();
	vector<string> difficulties(3); //difficulties w/o vs players
	difficulties[0] = "   easy   ";
	difficulties[1] = "  medium  ";
	difficulties[2] = "   hard   ";
	difficulties.shrink_to_fit();
	vector<string> firstsecond(2); //first or second
	firstsecond[0] = "  first   ";
	firstsecond[1] = "  second  ";
	firstsecond.shrink_to_fit();
	vector<MenuOption> settingsMenuOptions(5); //initializes the settings menu options
	vector<MenuOption> areYouSureOptions(2); //creates the are you sure options
	vector<MenuOption> exitMenuOptions(2); //exit menu options

	//initializes the are you sure menu
	areYouSureOptions[0].initialize("Yes"); 
	areYouSureOptions[1].initialize("No ");
	areYouSureOptions.shrink_to_fit();
	Menu areYouSureMenu(areYouSureOptions, "Are you sure you want to do this?", "The action you are attempting likely cannot be undone. Only proceed if you are sure.", alignCenter); //creates the are you sure menu

	//creates and initializes the exit menu
	exitMenuOptions[0].initialize("Exit Game");
	exitMenuOptions[1].initialize("Return to Game");
	exitMenuOptions.shrink_to_fit();
	Menu exitMenu(exitMenuOptions, "Exit Game", "Press Escape to return to the game. Select \"Exit Game\" to exit the game.", alignCenter);

	//creates and initializes the main menu
	vector<MenuOption> mainMenuOptions(5); //initializes the main menu options
	mainMenuOptions[0].initialize("Singleplayer");
	mainMenuOptions[1].initialize("Multiplayer");
	mainMenuOptions[2].initialize("Settings");
	mainMenuOptions[3].initialize("Manage Accounts");
	//mainMenuOptions[4].initialize("HighScores");
	mainMenuOptions[4].initialize("Exit");
	Menu mainMenu(mainMenuOptions, "Connect Four", "Use W and S to navigate up and down. Use A and D to change values. Use the Enter or Space key to select. Use ESC to exit.", alignLeft); //creates the main menu 

	//creates the game
	Game mainGame;

	//create the players
	Player player1(&mainGame);
	Player player2(&mainGame);

	//initializes the game
	mainGame.initialize(&player1, &player2, &exitMenu, &areYouSureMenu);

	//creates and initializes the settings menu
	int difficulty = 1;
	int aiGoes = 1;
	settingsMenuOptions[0].initialize("AI difficulty", textMenuOption, &difficulty, difficulties);
	settingsMenuOptions[1].initialize("Ai goes      ", textMenuOption, &aiGoes, firstsecond);
	settingsMenuOptions[2].initialize("Player 1 Colour", colourMenuOption, &mainGame.p1Col);
	settingsMenuOptions[3].initialize("Player 2 Colour", colourMenuOption, &mainGame.p2Col);
	settingsMenuOptions[4].initialize("Back");
	Menu settingsMenu(settingsMenuOptions, "Settings", "Use W and S to navigate up and Down. Use A and D to change values. Use Space, Enter or ESC to go back.", alignLeft);

	//creates and initializes the accounts from the file
	vector<PlayerAccount> userAccounts(0); //creates the vector of accounts
	PlayerAccount newAccount("[no name available]");
	ifstream accountsFileIn;
	accountsFileIn.open(fileName); //opens the file
	string fileInput;
	string userName; //creates temporary arrays to store the values from the file
	int wins[4];
	int losses[4];
	int totalTurns[4];
	bool endOfFile = false;
	for (int accountsCount = 0 ; accountsFileIn.is_open(); accountsCount++){ //while the file is still open
		getline(accountsFileIn, userName); //gets the user name from the file
		for (int i = 0; i < 4; i++){ //for each difficulty level
			getline(accountsFileIn, fileInput); //gets a line from the file
			if (isInteger(fileInput) && !accountsFileIn.eof()) { //checks that the line is an integer
				wins[i] = stoi(fileInput); //the line is saved as the number of wins
			}
			else { //if it is not an integer
				endOfFile = true; //saves that the end of the file was reached
				break; //exits the loop
			}
			getline(accountsFileIn, fileInput); //gets a line from the file
			if (isInteger(fileInput) && !accountsFileIn.eof()) { //checks that the line is an integer
				losses[i] = stoi(fileInput); //the line is saved as the number of losses
			}
			else { //if it is not an integer
				endOfFile = true; //saves that the end of the file was reached
				break; //exits the loop
			}
			getline(accountsFileIn, fileInput); //gets a line from the file
			if (isInteger(fileInput) && !accountsFileIn.eof()) { //checks that the line is an integer
				totalTurns[i] = stoi(fileInput); //the line is saved as the number of turns
			}
			else { //if it is not an integer
				endOfFile = true; //saves that the end of the file was reached
				break; //exits the loop
			}
		}	
		if (!endOfFile) { //if the end of the file or an error was not reached
			PlayerAccount tempAccount; //creates a temporary account with the info collected
			tempAccount.save(userName, wins, losses, totalTurns);
			userAccounts.push_back(tempAccount);  //adds it to the vector of accounts
		}
		else {
			accountsFileIn.close(); //closes the file if the end has been reached
			break;
		}
	}

	//creates the individual accounts menu
	vector<MenuOption> indivAccountsMenuOptions(7); //creates the menu options for the individual accounts modification screen
	int accountDetailsDifficulty = 0; //variable to keep track of the accounts details menu difficulty
	indivAccountsMenuOptions[0].initialize("Delete Account");  //delete account option
	indivAccountsMenuOptions[1].initialize("Change Name"); //change the name
	indivAccountsMenuOptions[2].initialize("Difficulty             ", textMenuOption, &accountDetailsDifficulty, statDifficulties); //difficulty option
	vector<string> statWins(4); //string with the number of wins at each difficulty
	vector<string> statLosses(4); //string with the number of losses at each difficulty
	vector<string> statTurnsPerWin(4); //string with the number of turns per win at each 
	indivAccountsMenuOptions[3].initialize("Wins:                  ", textMenuOption, &accountDetailsDifficulty, statWins); //wins
	indivAccountsMenuOptions[4].initialize("Losses:                ", textMenuOption, &accountDetailsDifficulty, statLosses); //losses
	indivAccountsMenuOptions[5].initialize("Average Turns Per Win: ", textMenuOption, &accountDetailsDifficulty, statTurnsPerWin); //Average turns per win
	indivAccountsMenuOptions[6].initialize("Exit");
	Menu indivAccountsMenu(indivAccountsMenuOptions, "");

	//The main menu/game
	bool exitGame = false;
	do { //repeats until they select to exit
		int mainMenuChoice = mainMenu.getSelection(); //outputs the main menu and gets the user's selection
		int accountsMenuChoice;
		int areYouSure;
		int indivAccMenuchoice;
		string newAccountName;

		//creates and initializes the accounts menu
		vector<MenuOption> accountsMenuOptions(userAccounts.size() + 2); //creates the accounts menu options vector
		for (size_t accounts = 0; accounts < accountsMenuOptions.size() - 2; accounts++){ //initializes each element of the accounts menu options
			accountsMenuOptions[accounts].initialize(userAccounts[accounts].getName());
		}
		accountsMenuOptions[accountsMenuOptions.size() - 2].initialize("Create New Account"); //intitializes the second last to create a new account
		accountsMenuOptions[accountsMenuOptions.size() - 1].initialize("Exit"); //initializes the last one to exit
		Menu accountsMenu(accountsMenuOptions, "Manage Accounts", "Use W and S to navigate up and down. Use Space or Enter to select.", alignLeft);
		
		int p1, p2;
		bool cont = false;
		bool exit = false;
		clearScreen(); //clears the screen
		_flushall();
		switch (mainMenuChoice){
		case 0: //if they chose to play singleplayer
			accountsMenu.setTitle("Player Account Selection"); 
			accountsMenu.changeMessage("Use W and S to navigate up and down. Use Space or Enter to select."); //changes the accounts menu selection title and message
			do {
				p1 = accountsMenu.getSelection(); //gets the player's account
				if (p1 == accountsMenuOptions.size() - 1){ //if the last option is selected nothing happens and it exits the menu
					exit = true; //signals exit
					cont = true;
					break;
				}
				else if (p1 == accountsMenuOptions.size() - 2){ //if create a new accounts is selected
					clearScreen(); //clears the screen and sets the cursor position
					setCursorPosition(19, 7);
					cout << "Please input the name of the new Account: ";
					setCursorPosition(19, 8);
					getline(cin, newAccountName); //gets the name of the new account
					newAccount.changeName(newAccountName); //creates a temporary account
					userAccounts.push_back(newAccount); //adds the new account to the accounts menu
					accountsMenuOptions.push_back(accountsMenuOptions[accountsMenuOptions.size() - 1]);
					accountsMenuOptions[accountsMenuOptions.size() - 2] = accountsMenuOptions[accountsMenuOptions.size() - 3];
					accountsMenuOptions[accountsMenuOptions.size() - 3].initialize(newAccountName); //adds the new account to the account selection menu
					accountsMenu.updateOptions(accountsMenuOptions); //updates the accounts selection menu
					cont = true;
				}
				else cont = true;
			} while (!cont);
			if (exit) break; //exits if exit was signaled
			settingsMenu.changeMessage("Use W and S to navigate up and Down. Use A and D to change values. Press Space or Enter to continue. Select exit to return to main menu.");
			if (settingsMenu.getSelection() == settingsMenuOptions.size() - 1) break; //breaks if exit was chosen from the settings menu

			if (aiGoes == 1) { //if the ai goes second
				player1.setPlayer(againstPlayer, &userAccounts[p1]); //sets player 1
				player2.setPlayer(difficulty); //sets the ai
			}
			else { //if the ai goes first
				player2.setPlayer(againstPlayer, &userAccounts[p1]); //sets player 1
				player1.setPlayer(difficulty); //sets the ai
			}
			mainGame.initialize(&player1, &player2, &exitMenu, &areYouSureMenu);
			mainGame.game(); //runs the main game
			break;
		case 1: //if they chose multiplayer
			accountsMenu.setTitle("Player 1 Account Selection");
			accountsMenu.changeMessage("Use W and S to navigate up and down. Use Space or Enter to select."); //changes the accounts menu selection title and message
			p1 = accountsMenu.getSelection(); //gets player 1's account
			if (p1 == accountsMenuOptions.size() - 1){ //if the last option is selected nothing happens and it exits the menu
				break;
			}
			else if (p1 == accountsMenuOptions.size() - 2){ //if create a new accounts is selected
				clearScreen(); //clears the screen and sets the cursor position
				setCursorPosition(19, 7);
				cout << "Please input the name of the new Account: ";
				setCursorPosition(19, 8);
				getline(cin, newAccountName); //gets the name of the new account
				newAccount.changeName(newAccountName); //creates a temporary account
				userAccounts.push_back(newAccount); //adds the new account to the accounts menu
				accountsMenuOptions.push_back(accountsMenuOptions[accountsMenuOptions.size() - 1]);
				accountsMenuOptions[accountsMenuOptions.size() - 2] = accountsMenuOptions[accountsMenuOptions.size() - 3];
				accountsMenuOptions[accountsMenuOptions.size() - 3].initialize(newAccountName); //adds the new account to the account selection menu
				accountsMenu.updateOptions(accountsMenuOptions); //updates the accounts selection menu
				p1 = accountsMenuOptions.size() - 3;
			}
			if (exit) break; //exits if exit was signaled
			accountsMenu.setTitle("Player 2 Account Selection"); //changes the accounts menu selection title and message
			accountsMenu.changeMessage("Use W and S to navigate up and down. Use Space or Enter to select. Cannot choose the samme account as Player 1."); 
			player1.setPlayer(againstPlayer, &userAccounts[p1]); //saves player1
			do {
				p2 = accountsMenu.getSelection(); //gets player 2's account
				if (p2 == accountsMenuOptions.size() - 1){ //if the last option is selected nothing happens and it exits the menu
					exit = true; //signals exit
					break;
				}
				else if (p2 == accountsMenuOptions.size() - 2){ //if create a new accounts is selected
					clearScreen(); //clears the screen and sets the cursor position
					setCursorPosition(19, 7);
					cout << "Please input the name of the new Account: ";
					setCursorPosition(19, 8);
					getline(cin, newAccountName); //gets the name of the new account
					PlayerAccount newAccount(newAccountName); //creates a temporary account
					userAccounts.push_back(newAccount); //adds the new account to the accounts menu
					accountsMenuOptions.push_back(accountsMenuOptions[accountsMenuOptions.size() - 1]);
					accountsMenuOptions[accountsMenuOptions.size() - 2] = accountsMenuOptions[accountsMenuOptions.size() - 3];
					accountsMenuOptions[accountsMenuOptions.size() - 3].initialize(newAccountName); //adds the new account to the account selection menu
					accountsMenu.updateOptions(accountsMenuOptions); //updates the accounts selection menu
					p2 = accountsMenuOptions.size() - 3;
				}
			} while (p2 == p1);
			if (exit) break; //exits if exit was signaled
			player2.setPlayer(againstPlayer, &userAccounts[p2]); //saves player 2
			mainGame.initialize(&player1, &player2, &exitMenu, &areYouSureMenu);
			mainGame.game(); //runs the main game
			break;
		case 2: //if they chose the settings
			settingsMenu.changeMessage("Use W and S to navigate up and Down. Use A and D to change values. Use Space, Enter or ESC to go back.");
			settingsMenu.getSelection(); //settings menu is displayed
			break;
		case 3: //if they chose to manage accounts
			accountsMenu.setTitle("Manage Accouts"); //changes the title
			accountsMenu.changeMessage("Use W and S to navigate up and down. Use Space or Enter to select.");
			accountsMenuChoice = accountsMenu.getSelection(); //outputs the accounts menu and gets the user's 
			if (accountsMenuChoice == accountsMenuOptions.size() - 1); //if the last option is selected nothing happens and it exits the menu
			else if (accountsMenuChoice == accountsMenuOptions.size() - 2){ //if create a new accounts is selected
				clearScreen(); //clears the screen and sets the cursor position
				setCursorPosition(19, 7); 
				cout << "Please input the name of the new Account: ";
				setCursorPosition(19, 8);
				getline(cin, newAccountName); //gets the name of the new account
				PlayerAccount newAccount(newAccountName); //creates a temporary account
				userAccounts.push_back(newAccount); //adds the new account to the accounts menu
			}
			else { //otherwise an accounts is modified
				indivAccountsMenu.setTitle(userAccounts[accountsMenuChoice].getName()); //sets the title to the account name
				for (int dif = 0; dif < 4; dif++){ //for each difficulty
					string w = to_string(userAccounts[accountsMenuChoice].getWins(dif)); //converts the number of wins to a string
					string l = to_string(userAccounts[accountsMenuChoice].getLosses(dif)); //converts the number of losses to a string
					string t = to_string(userAccounts[accountsMenuChoice].getTurnsPerWin(dif)); //converts the turns per win to a string
					if (t.find(".") != string::npos && t.find(".") + 2 < t.size()) t = t.substr(0,t.find(".") +3); //makes sure the turns per win doesnt have to many digits
					if (l.length() < 10) for (int i = l.length(); i < 10; i++) l = " " + l; //the strings are padded with '0's to make it 10 characters long
					if (w.length() < 10) for (int i = w.length(); i < 10; i++) w = " " + w;
					if (t.length() < 10) for (int i = t.length(); i < 10; i++) t = " " + t;
					statWins[dif] = w; //saves the wins to a temporary vector
					statLosses[dif] = l; //saves the losses
					statTurnsPerWin[dif] = t; //saves the turns per win
				} //update the stats for the menu options
				indivAccountsMenuOptions[3].changeValues(statWins); //updates the number of wins
				indivAccountsMenuOptions[4].changeValues(statLosses);  //updates the number of losses
				indivAccountsMenuOptions[5].changeValues(statTurnsPerWin); //updates the number of turns
				indivAccountsMenu.updateOptions(indivAccountsMenuOptions); //updates the options for the account menu
				while (1) {
					indivAccMenuchoice = indivAccountsMenu.getSelection();//gets the user's selection for the user accounts menu
					if (indivAccMenuchoice == 0 && !areYouSureMenu.getSelection()){ //if they choose to delete the account and say they are sure
						userAccounts.erase(userAccounts.begin() + accountsMenuChoice);  //deletes the account
						break;
					}
					else if (indivAccMenuchoice == 1){ //if they choose to change the name
						clearScreen(); //clears the screen and sets the cursor position
						setCursorPosition(19, 7);
						cout << "Please input the new name: ";
						setCursorPosition(19, 8);
						getline(cin, newAccountName); //gets the new name of the account
						userAccounts[accountsMenuChoice].changeName(newAccountName); //changes the name
						indivAccountsMenu.setTitle(userAccounts[accountsMenuChoice].getName()); //sets the title to the account name
					}
					else break;
				}
			}
			break;
		case 4: //if exit is chosen
			exitGame = true; //closes the program
			break;
		}
	} while (!exitGame);

	//save the accounts to a file
	ofstream accountsFileOut;
	accountsFileOut.open(fileName, std::ios::trunc); //opens the file to output
	for (size_t i = 0; i < userAccounts.size(); i++){ //for each accounts
		accountsFileOut << userAccounts[i].getName() << endl; //outputs the name to the file
		for (int count = 0; count < 4; count++) { //for each difficulty level
			accountsFileOut << userAccounts[i].getWins(count) << endl; //saves the wins, losses and turns
			accountsFileOut << userAccounts[i].getLosses(count) << endl;
			accountsFileOut << userAccounts[i].getTotalTurns(count) << endl;
		}
	}
	accountsFileOut.close();//closes the file
}