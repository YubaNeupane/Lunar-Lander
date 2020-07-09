#include "LunarSurface.h"

#include <cstdlib>

#include <ctime>

#include <fstream>

#include <iomanip>

#include <iostream>

#include <string>

#include <vector>



using namespace std;





LunarSurface::LunarSurface() {



} // Constructor

LunarSurface::~LunarSurface() {



} // Destructor



bool LunarSurface::readBoardFile(string fileName) {

    ifstream outFile;

    outFile.open(fileName);

    bool test = outFile.fail();



    if (!test) {

        //2D array

        char tempStore;

        string line;

        int j = 0;

        while (getline(outFile, line)) {

            for (int i = 0; i < line.length(); i++) {

                tempStore = line[i];

                board[j][i] = tempStore;

                board[j + 1][i] = tempStore;

                board[j][i + 1] = tempStore;

                board[j][i + 1] = tempStore;

            }



            j++;

        }

        //Checking board

        cout << "\n" << endl;

        for (int i = 0; i < ROWS; i++) {

            for (int j = 0; j < COLS; j++) {

                tempStore = board[i][j];



                if (!(tempStore == ' ' || tempStore == 'X' || tempStore == 'F' || tempStore == '$' || tempStore == '-')) {

                    return false;

                }

            }

        }



        cout << "     |";

        cout << setw(1);

        for (int i = 0; i < 4; i++) {

            for (int j = 0; j < 10; j++) {

                cout << " " << i;

            }

        }

        cout << endl;

        cout << "     |";

        cout << setw(1);

        for (int i = 0; i < 10; i++) {

            for (int j = 0; j < 4; j++) {

                cout << " " << i;

            }



        }

        cout << endl;

        cout << right << setw(3) << "-----+--------------------------------------------------------------------------------" << endl;



        for (int i = 0; i < ROWS; i++) {

            vector < string > temp;

            string tempString;



            if (i >= 10) {

                cout << right << setw(3) << " " << left << i << "|";

            }
            else {

                cout << right << setw(4) << " " << left << i << "|";

            }



            for (int j = 0; j < COLS; j++) {



                tempString += board[i][j];

                tempString += board[i][j];

                cout << board[i][j];

                cout << board[i][j];

            }

            cout << endl;

            temp.push_back(tempString);

            cout << right << setw(6) << "|" << temp[0];

            cout << endl;



        }

        cout << "\n\n";

        return true;

    }

    return false;

}



char LunarSurface::getBoardUnit(int row, int col) {

    return board[row][col];

}

void LunarSurface::setBoardUnit(int row, int col, char inChg) {

    board[row][col] = inChg;

}