//Theo Vanderkooy
//ICS 3UI Summative
//Connect Four
#pragma once

//c++ library includes
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdlib>
#include<string>
#include<vector>
#include<Windows.h>
#include<conio.h>
#include<stdio.h>
#include<fstream>

//usings
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::to_string;
using std::getline;
using std::cin;
using std::rand;
using std::srand;

//other header file includes
#include"OtherFunctions.h"
#include"Menu.h"
#include"MenuOptions.h"
#include"PlayerAccount.h"
#include"Game.h"
#include"Player.h"
#include"FakeGame.h"

//cursor colour definitions
#define highlightColourBack 0
#define highlightColourText 15

//key input definitions
#define upKey 119 //W
#define downKey 115 //S
#define leftKey 97 //A
#define rightKey 100 //D
#define enterKey 13 
#define escKey 27 
#define spaceKey 32 

//player two key inputs
#define p2Left 106 //J key
#define p2Right 108 //L key
#define p2Down 107 //K key

//alignments
#define alignLeft 0
#define alignCenter 1

//menu option types
#define regularMenuOption 0
#define numberMenuOption 1
#define textMenuOption 2
#define colourMenuOption 3

//for player win/loss ratios/difficulty levels
#define againstEasy 0
#define againstMedium 1
#define againstHard 2
#define againstPlayer 3

//for file openings
#define fileName "userAccounts" //user accounts file

//for assigning values to board locations
#define bothPlayersWin 3276800
#define threeOtherPieces 409600 
#define twoPiecesBothEnds 51200 
#define twoOtherPieces 6400 
#define oneOtherPiece 800 
#define emptyRow 100
#define useless 1

#define centerModifier 1.05
#define oneOutModifier 1.03
#define twoOutModifier 1.01
#define threeOutModifier 1

//for timings
#define moveTime 500 //in ms

//for recursions
#define recursionDepth 3
#define colDepth 4

//for column values
enum ColVal { 
	winBlock,      //0  both players can win in that spot/column
	partOfWin,     //1  if spot is part of 2 or more wins in a row
	winNow,        //2  will win the game
	blockNow,      //3  needs to be blocked
	willWin1,      //4  the column will win after a turn
	willWin2,      //5  the column will win after 2 plays in that column
	useful,        //6  spot is useful to ai
	dangerous,     //7  spot is useful to the other person
	neutral,       //8  nothing special
	enablesBlock,  //9  allows the player to block a useful spot
	enablesMove,   //10 opens up a dangerous spot for the player
	winAbove,      //11 the other player can block a win above
	doNotPlay,     //12 the other person can win on top
	wbAbove,       //13 both players can win above
	cantPlay       //14 the column is full
}; 