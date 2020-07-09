#include <iostream>
#include <string>
#include "LunarSurface.h"
#include "LunarRover.h"
#include<conio.h>
using namespace std;

void playagain(bool& wantToPlayAgain);
void outEndingOutput(bool& wantToPlayAgain, string filename, LunarSurface gameBoard, string outputLable);

int main()
{
    LunarSurface Board;
    LunarSurface* BoardPointer = &Board;
    LunarRover rover(BoardPointer);

    int row, columns;

    string filename;
    bool open;

    cout << "Specify a board file :";
    cin >> filename;
    open = Board.readBoardFile(filename);
    bool toplayagain = true;


    while (open == false)
    {
        cout << endl << "File read error for board file : " << filename << endl;
        cout << endl << "Either the file does not exist or does not contain a valid board file! " << endl;
        cout << "Specify a different board file : ";
        cin >> filename;
        open = Board.readBoardFile(filename);
    }

    while (toplayagain) {
        cout << "Enter (row, col) coordinates: ";
        cin >> row >> columns;
        bool land = rover.land(row, columns);
        if (!land) {
            cout << "Crash you lose!" << endl;
            playagain(toplayagain);
            if (!toplayagain) {
                break;
            }
        }
        rover.setFuel(100);
        rover.setDamage(0);
        rover.setPosition(row, columns);
        rover.drawGrid();

        while (true) {
            int didDie;
            char dir;
            cout << "Enter a move (W (up),A (do wn), S (left), D (right)): ";
            cin >> dir;


            if (toupper(dir) == 'W') {
                row -= 1;
                didDie = rover.move(row, columns);
                rover.drawGrid();
            }
            else if (toupper(dir) == 'S') {
                row += 1;
                didDie = rover.move(row, columns);
                rover.drawGrid();
            }
            else if (toupper(dir) == 'A') {
                columns -= 1;
                didDie = rover.move(row, columns);
                rover.drawGrid();

            }
            else if (toupper(dir) == 'D') {
                columns += 1;
                didDie = rover.move(row, columns);
                rover.drawGrid();
            }
            else {
                cout << "Invalid Input!" << endl;
            }

            if (didDie == -1) {
                outEndingOutput(toplayagain, filename, Board, "Crashed you in impossible terrain, better luck next time!");
                break;
            }
            if (didDie == 6) {
                outEndingOutput(toplayagain, filename, Board, "You ran out fuel, better luck next time!");
                break;
            }
            if (didDie == 5) {
                outEndingOutput(toplayagain, filename, Board, "You Win!");
                break;
            }
            if (didDie == 2) {
                outEndingOutput(toplayagain, filename, Board, "Your little rover couldn't take all the damage from rough terrain, better luck next time!");
                break;
            }
            if (didDie == 3) {
                outEndingOutput(toplayagain, filename, Board, "You ran out of fuel! Take a better route next time!");
                break;
            }
        }
    }


    system("PAUSE");
    return 0;
}


void playagain(bool& wantToPlayAgain) {
    while (true) {
        char userInput;
        cout << "Would you like to play again? (Y/N)? ";
        cin >> userInput;
        if (toupper(userInput) == 'Y') {
            wantToPlayAgain = true;
            system("CLS");
            break;
        }
        else if (toupper(userInput) == 'N') {
            wantToPlayAgain = false;
            break;
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
}
void outEndingOutput(bool& wantToPlayAgain, string filename, LunarSurface gameBoard, string outputLable) {
    cout << outputLable << "\n" << endl;
    playagain(wantToPlayAgain);
    if (wantToPlayAgain) gameBoard.readBoardFile(filename);
}