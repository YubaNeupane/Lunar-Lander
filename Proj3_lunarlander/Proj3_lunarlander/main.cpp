#include <iostream>
#include "LunarRover.h"
#include "LunarSurface.h"
#include <Windows.h>
#include <cctype>

#include <string>

using namespace std;

void changeFontSize(int sizeX, int sizeY);
bool landPlayer(LunarRover &rover);
bool playAgain();

void displayMenu();
void displaySetting(bool hideFuelAndTarget, bool soundMuted);
void playSound(bool soundMuted, int hz, int length);
void diplayLunarLander();

int main()
{
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    
    changeFontSize(0, 30);

    string fileName;
    LunarSurface gameSurface;
    LunarSurface* ptrGameSurface = &gameSurface;
    LunarRover rover(ptrGameSurface);

    bool hideFuelAndTarget = false;
    bool soundMuted = false;

    bool gameSatus = true;

    //MENU
    while (true) {
        int userChoice;
        
        displayMenu();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "\nChoice the option with a number: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cin >> userChoice;
        if (userChoice == 1) {
            playSound(soundMuted, 150,200);
            break;
        }
        else if (userChoice == 2) {
            playSound(soundMuted, 150, 200);
            while (true) {
                system("CLS");
                displaySetting(hideFuelAndTarget,soundMuted);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                cout << "\nChoice the option with a number: ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                cin >> userChoice;
                if (userChoice == 1) {
                    playSound(soundMuted, 150, 200);

                    if (hideFuelAndTarget) {
                        hideFuelAndTarget = false;
                    }
                    else {
                        hideFuelAndTarget = true;
                    }
                }
                else if (userChoice == 2) {
                    playSound(soundMuted, 150, 200);
                    if (soundMuted) {
                        soundMuted = false;
                    }
                    else {
                        soundMuted = true;
                    }
                }else if (userChoice == 3) {
                    playSound(soundMuted, 150,200);
                    break;
                }
                else {
                    cout << "Invalid input" << endl;
                    playSound(soundMuted, 150, 500);
                }
            }
        }
        else if (userChoice == 3) {
            system("exit");
            return 0;
        }
        else {
            cout << "Invalid input, try again";
            Sleep(1000);
        }
        system("cls");

    }
    system("cls");


    changeFontSize(0, 30);

    //Getting file info to open
    bool hasFileLoaded = gameSurface.readBoardFile("board.txt");
    if (!hasFileLoaded) {
        cout << "Error loading default board file!" << endl;
        cout << "Either \"board.txt\" doesn't exist or doesn't contain a valid board file\n" << endl;
        while (!hasFileLoaded) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "Specify a diffrent board file: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cin >> fileName;
            hasFileLoaded = gameSurface.readBoardFile(fileName);
            Sleep(1000);
            system("CLS");
        }
    }
    changeFontSize(0, 24);

    while (gameSatus){
        rover.setFuel(100);
        rover.setDamage(0);
        rover.drawGrid(hideFuelAndTarget);
        
        int userRow{}, userCol{};

        bool hasLanded = landPlayer(rover);
        if (!hasLanded) { 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "\nCrash, Sorry you lose!" << endl;
            gameSatus = playAgain();
            continue;
        }

        while (true) {
            int validateMovemment{ 1 };
            rover.drawGrid();
            char dirInput{};
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "Enter a move (W (up), A (left), S (down) , D (right) Q(quit): ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cin >> dirInput;
            dirInput = toupper(dirInput);

            int roverCol{}, roverRow{};
            rover.getPosition(roverRow,roverCol);

            if (dirInput == 'W') {
                playSound(soundMuted, 180, 500);
                validateMovemment = rover.move(roverRow - 1, roverCol);

            }
            else if (dirInput == 'A') {
                playSound(soundMuted, 180, 500);
                validateMovemment = rover.move(roverRow, roverCol-1);
            }
            else if (dirInput == 'S') {
                playSound(soundMuted, 180, 500);
                validateMovemment = rover.move(roverRow+1, roverCol);
            }
            else if (dirInput == 'D') {
                playSound(soundMuted, 180, 500);
                validateMovemment = rover.move(roverRow, roverCol+1);
            }
            else if (dirInput == 'Q') {
                 system("exit");
                return 0;
            }
            else {
                cout << "Invalid input!" << endl;
                Sleep(500);
            }

            if (validateMovemment == -1) {
                playSound(soundMuted, 600, 500);
                cout << "Crash you in impassable terrain, better luck next time!" << endl;
                gameSatus = playAgain();
                if(gameSatus == true) gameSurface.readBoardFile(fileName);
                break;
            }
            if (validateMovemment == 6) {
                playSound(soundMuted, 600, 500);
                cout << "You ran out fuel, better luck next time!" << endl;
                gameSatus = playAgain();
                if (gameSatus == true) gameSurface.readBoardFile(fileName);
                break;
            }
            if (validateMovemment == 5) {
                playSound(soundMuted, 600, 500);
                cout << "Congratulation! You've reached the target - one small step for man, one giant leap for mankind!" << endl;
                gameSatus = playAgain();
                if (gameSatus == true) gameSurface.readBoardFile(fileName);
                break;
            }
            if (validateMovemment == 2) {
                playSound(soundMuted, 600, 500);
                cout << "Your rover couldn't take all the damage from rough terrain, better luck next time!" << endl;
                gameSatus = playAgain();
                if (gameSatus == true) gameSurface.readBoardFile(fileName);
                break;
            }
            if (validateMovemment == 3) {
                playSound(soundMuted, 600, 500);
                cout << "You ran out of fuel! Take a better route next time!" << endl;
                gameSatus = playAgain();
                if (gameSatus == true) gameSurface.readBoardFile(fileName);
                break;
            }
           
        }
    }
    system("exit");
    return 0;
}
bool landPlayer(LunarRover &rover) {
    int row{}, col{};
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\nEnter (row, col) coordinates: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cin >> row >> col;
    return rover.land(row, col);
}

bool playAgain() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    while (true) {
        char userInput;
        cout << "Would you like to play again (Y/N): ";
        cin >> userInput;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        if (toupper(userInput) == 'Y') {
            return true;
           
        }
        else if (toupper(userInput) == 'N') {
            return false;
           
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
}

void playSound(bool soundMuted, int hz, int length){
    if (!soundMuted) {
        Beep(hz, length);
    }
}

void diplayLunarLander() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << " ___      __   __  __    _  _______  ______              ___      _______  __    _  ______   _______  ______   " << endl;
    cout << "|   |    |  | |  ||  |  | ||   _   ||    _ |            |   |    |   _   ||  |  | ||      | |       ||    _ |  " << endl;
    cout << "|   |    |  | |  ||   |_| ||  |_|  ||   | ||            |   |    |  |_|  ||   |_| ||  _    ||    ___||   | ||  " << endl;
    cout << "|   |    |  |_|  ||       ||       ||   |_||_           |   |    |       ||       || | |   ||   |___ |   |_||_ " << endl;
    cout << "|   |___ |       ||  _    ||       ||    __  |          |   |___ |       ||  _    || |_|   ||    ___||    __  |" << endl;
    cout << "|       ||       || | |   ||   _   ||   |  | |          |       ||   _   || | |   ||       ||   |___ |   |  | |" << endl;
    cout << "|_______||_______||_|  |__||__| |__||___|  |_|          |_______||__| |__||_|  |__||______| |_______||___|  |_|" << endl;
    cout << endl;
    cout << endl;
}

void displayMenu() {
    diplayLunarLander();


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\nMENU: \n" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "1. PLAY GAME" << endl;
    cout << "2. SETTING" << endl;
    cout << "3. QUIT" << endl;   
}

void displaySetting(bool hideFuelAndTarget, bool soundMuted) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\nSETTING: \n" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << boolalpha << "1. HIDE FUEL AND TARGET WHILE LANDING: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << hideFuelAndTarget  << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << boolalpha << "2. MUTE SOUND: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << soundMuted << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "3. BACK" << endl;
}

void changeFontSize(int sizeX, int sizeY) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = sizeX;                 
    cfi.dwFontSize.Y = sizeY;                 
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}