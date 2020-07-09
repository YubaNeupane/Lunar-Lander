#include "LunarSurface.h"
#include <fstream>
#include <iostream>
using namespace std;

LunarSurface::LunarSurface()
{
}

LunarSurface::~LunarSurface()
{
}

bool LunarSurface::readBoardFile(string filename)
{
    if (filename.rfind(".") != -1) {
        if (filename.substr(filename.rfind(".")) == ".txt") {
            int y = 0;
            ifstream inputFile;
            inputFile.open(filename);
            if (!inputFile.fail()) {
                
                while (!inputFile.eof()) {
                    string line{};
                    getline(inputFile, line);
                    for (int i = 0; i < line.length(); i++) {
                        if (line[i] == UNITFUEL || line[i] == UNITIMPASSABLE || line[i] == UNITSAFE || line[i] == UNITROUGH || line[i] == UNITTARGET) {
                            board[y][i] = line[i];
                        }
                        else {
                            cout << "Not valid game board!" << endl;
                            return false;
                        }
                    }
                    y++;
                }

                return true;
            }
            else {
                cout << "Error loading " << filename << ". Try again!" << endl;
                return false;
            }
         
        }
        else {
            cout << "Invalid file, ex: filename.txt" << endl;
            return false;
        }
    }
    else {
        cout << "Invalid file, ex: filename.txt" << endl;
        return false;
    }
	return false;
}

char LunarSurface::getBoardUnit(int row, int col)
{
    return board[row][col];
}

void LunarSurface::setBoardUnit(int row, int col, char inChg)
{
    board[row][col] = inChg;
}
