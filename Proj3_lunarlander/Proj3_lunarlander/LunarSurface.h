#pragma once
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Define some codes and other necessary game-play parameters
// You don't have to use these constants, but they will make programming your
// game easier and more legible to people reading your code!
const int ROWS = 15, COLS = 40;
const int COLSP = 3;
const int ROWSP = 4;
const int BORDERCOLLISION = -1;
const int IMPASSABLECOLLISION = -2;
const int TARGETCOLLISION = -3;
const int MAXDAMAGE = -4;
const int NOFUEL = -5;
const char UNITSAFE = ' ';
const char UNITROUGH = '-';
const char UNITFUEL = 'F';
const char UNITTARGET = '$';
const char UNITIMPASSABLE = 'X';



class LunarSurface {
public:
	LunarSurface();										// Constructor
	~LunarSurface();									// Destructor

	bool readBoardFile(string filename);				// Initialize the board via reading a file
		// This function attempts to open filename for input (ifstream). If the file was opened successfully,
		// then read in the (ROWS x COLS) board and store each unit in the 2D board array
		// Return true if the file was opened and the board was read
		// Return false if the file was not able to be opened. 

	char getBoardUnit(int row, int col);				// return the char at (row, col) in the 2D board array
		// Determine the unit type for a specified position. This function is simple, just return board[row][col]!

	void setBoardUnit(int row, int col, char inChg);	// Set the unit type for a specified position
		// Remember, you will want to update the game board if the user lands on a consumable item like food.
		// Don't forget, you can add other consumable items as part of the bonus, such as repair equipment!

	struct position {
		int row{0};
		int col{0};
	};


private:

	char board[ROWS][COLS]{};								// The actual board read in from file
};