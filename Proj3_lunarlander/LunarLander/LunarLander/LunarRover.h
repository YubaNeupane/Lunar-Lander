#pragma once
#include "conio.h"			// This probably won't work in Cloud9, you'll have to clear screen another way
#include "LunarSurface.h"	// LunarSurface specification file

class LunarRover
{
public:
	LunarRover(LunarSurface* inBoard);			// Constructor - need a valid LunarSurface pointer
	~LunarRover();								// Destructor - might not need to do anything here

public:
	void drawGrid();							// Draw the board
		// use a loop to go through all rows and cols of the game board (gameBoard->getBoardUnit(row, col)) 
		// Hint: store board units in a temporary 2D array before drawing them - that way, you can store 
		// the rover's position in the temp 2D array and THEN loop and draw the board to the screen
		// 2nd Hint: if you are programming in visual studio you can use <conio.h> functions to automatically
		// clear the screen before you draw (system("clear");). Otherwise, you have to print blank lines so 
		// you don't see the previous board state from the last move

	bool land(int row, int col);				// Initial landing of the rover
		// Use calls to gameBoard->getBoardUnit() to determine what unit the rover is landing on
		// if the rover tries to land on a safe position, return true. Otherwise, return false
		// Don't forget to update the rover's position if it lands on a safe unit

	int	 move(int newrow, int newcol);			// Move the rover and return outcome
		// Use calls to gameBoard->getBoardUnit() to determine what unit the rover is moving to
		// depending on the unit moved to, return the status of what happened
		// don't forget to update the rover's fuel, damage, and position here as well!


	void getPosition(int& oldrow, int& oldcol);	// Get current position of the rover on the board
	void setPosition(int newrow, int newcol);	// Update the rover position without outcome

	int	 getDamage();							// Get the rover's damage status
	void setDamage(int newdmg);					// Set the rover's damage status

	int	 getFuel();								// Get the rover's fuel status
	void setFuel(int newfuel);					// Set the rover's fuel status

private:
	LunarSurface* gameBoard;					// A pointer to a valid game board (LunarSurface class)
	int rowPOS, colPOS;							// The rover's position on the game board
	int fuel;									// Rover's fuel level (start at 100)
	int damage;									// Rover's damage level (start at 0)
};