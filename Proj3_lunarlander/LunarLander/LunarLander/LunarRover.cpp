#include "LunarRover.h"
#include "LunarSurface.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

char oldValue;
LunarRover::LunarRover(LunarSurface* inBoard) {
    gameBoard = inBoard;
    setFuel(100);
    rowPOS = -1;
    colPOS = -1;
}

LunarRover::~LunarRover() {

}

void LunarRover::setPosition(int newrow, int newcol) {



    oldValue = gameBoard->getBoardUnit(newrow, newcol);
    gameBoard->setBoardUnit(newrow, newcol, 'L');
    rowPOS = newrow;
    colPOS = newcol;
}
void LunarRover::drawGrid() {
    system("CLS");
    cout << endl;
    cout << "    |";
    cout << right << setw(3);
    for (int i = 0; i < COLS; i++) {
        cout << setw(3) << i;

    }
    cout << endl;
    cout << right << setw(2) << "----+-------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < ROWS; i++) {
        vector < string > temp;
        string tempString;

        if (i >= 10) {
            cout << right << setw(1) << " " << left << i << " | ";
        }
        else {
            cout << right << setw(2) << " " << left << i << " | ";
        }

        for (int j = 0; j < COLS; j++) {
            cout << gameBoard->getBoardUnit(i, j);
            cout << gameBoard->getBoardUnit(i, j);
            cout << gameBoard->getBoardUnit(i, j);

        }

        if (i == 0) {
            cout << "     FUEL:" << right << setw(5) << getFuel();
        }
        else if (i == 1) {
            cout << "   DAMAGE:" << right << setw(5) << getDamage();
        }

        cout << endl;

    }
    cout << "\n\n";

}

bool LunarRover::land(int row, int col) {

    char gameUnit = gameBoard->getBoardUnit(row, col);

    if (gameUnit != UNITIMPASSABLE) return true;

    return false;
}

int	 LunarRover::move(int newrow, int newcol) {
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
    }
    if (gameBoard->getBoardUnit(newrow, newcol) == '-') {
        setDamage(getDamage() + 8);
    }
    setFuel(fuel - 2);
    setPosition(newrow, newcol);
    return 1;



}

void  LunarRover::getPosition(int& oldrow, int& oldcol) {
    if (oldValue == 'F') {
        gameBoard->setBoardUnit(rowPOS, colPOS, ' ');
    }
    else {
        gameBoard->setBoardUnit(rowPOS, colPOS, oldValue);
    }
}
int	  LunarRover::getDamage() {
    return damage;

}
void LunarRover::setDamage(int newdmg) {
    damage = newdmg;
}
int	 LunarRover::getFuel() {
    return fuel;
}
void LunarRover::setFuel(int newfuel) {
    fuel = newfuel;
}