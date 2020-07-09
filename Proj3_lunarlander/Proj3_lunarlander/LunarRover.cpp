#include "LunarRover.h"
#include "LunarSurface.h"
#include <Windows.h>

//color codes
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define BLINK 128

char oldChar = {};
LunarRover::LunarRover(LunarSurface* inBoard)
{

	gameBoard = inBoard;
}

LunarRover::~LunarRover()
{
}

void LunarRover::drawGrid(bool hidenOnStart)
{
	system("CLS");
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
	cout << "    |";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTBLUE);
	cout << right << setw(3);
	for (int i = 0; i < COLS; i++) {
		cout << setw(3) << i;

	}
	cout << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
	cout << right << setw(2) << "----+-------------------------------------------------------------------------------------------------------------------------" << endl;


	for (int i = 0; i < ROWS; i++) {
		if (i >= 10) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BROWN);
			cout << right << setw(1) << " " << left << i;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
			cout << " | ";
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BROWN);
			cout << right << setw(2) << " " << left << i;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTRED);
			cout << " | ";
		}

	
		
		for (int j = 0; j < COLS; j++) {
			if (gameBoard->getBoardUnit(i, j) == UNITIMPASSABLE) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), RED);
			}
			else if (gameBoard->getBoardUnit(i, j) == UNITROUGH) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARKGREY);
			}
			else if (gameBoard->getBoardUnit(i, j) == UNITFUEL) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLUE);
			}
			else if (gameBoard->getBoardUnit(i, j) == UNITTARGET) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), LIGHTGREEN);
			}
			else if (gameBoard->getBoardUnit(i, j) == 'L') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
			}
			else {
			}

			if (hidenOnStart) {
				if (gameBoard->getBoardUnit(i, j) == UNITFUEL || gameBoard->getBoardUnit(i, j) == UNITTARGET) {
					cout << " ";
					cout << " ";
					cout << " ";
				}
				else {
					cout << gameBoard->getBoardUnit(i, j);
					cout << gameBoard->getBoardUnit(i, j);
					cout << gameBoard->getBoardUnit(i, j);
				}
			}
			else {
				cout << gameBoard->getBoardUnit(i, j);
				cout << gameBoard->getBoardUnit(i, j);
				cout << gameBoard->getBoardUnit(i, j);
			}
		}
		if (i == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			cout << "     FUEL:" << right << setw(5) << getFuel();
		}
		else if (i == 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAGENTA);
			cout << "   DAMAGE:" << right << setw(5) << getDamage();
		}
		cout << endl;

	}

}


bool LunarRover::land(int row, int col)
{
	if (row > ROWS || col > COLS || row < 0 || col < 0) {
		return false;
	}
	if (gameBoard->getBoardUnit(row, col) != UNITIMPASSABLE) {
		oldChar = gameBoard->getBoardUnit(row, col);
		setPosition(row, col);
		gameBoard->setBoardUnit(row, col, 'L');
		return true;
	}
	return false;
}

int LunarRover::move(int newrow, int newcol)
{
	getPosition(rowPOS, colPOS);

	if (getDamage() > 95) {
		return 2;
	}
	if (getFuel() < 0) {
		return 6;
	}

	if (gameBoard->getBoardUnit(newrow, newcol) == 'X') {
		return -1;
	}

	if (gameBoard->getBoardUnit(newrow, newcol) == '$') {
		return 5;
	}
	if (gameBoard->getBoardUnit(newrow, newcol) == 'F') {
		setFuel(getFuel() + 25);
		if (getFuel() > 100) {
			setFuel(100);
		}
		gameBoard->setBoardUnit(newrow, newcol, ' ');
	}
	if (gameBoard->getBoardUnit(newrow, newcol) == '-') {
		setDamage(getDamage() + 8);
	}
	setFuel(fuel - 2);
	gameBoard->setBoardUnit(rowPOS, colPOS, oldChar);
	setPosition(newrow, newcol);
	return 1;
}

void LunarRover::getPosition(int& oldrow, int& oldcol)
{
	oldrow = rowPOS;
	oldcol  = colPOS;
}

void LunarRover::setPosition(int newrow, int newcol)
{
	oldChar = gameBoard->getBoardUnit(newrow, newcol);
	gameBoard->setBoardUnit(newrow, newcol, 'L');
	rowPOS = newrow;
	colPOS = newcol;
}

int LunarRover::getDamage()
{
	return damage;
}

void LunarRover::setDamage(int newdmg)
{
	damage = newdmg;
}

int LunarRover::getFuel()
{
	return fuel;
}

void LunarRover::setFuel(int newfuel)
{
	fuel = newfuel;
}
