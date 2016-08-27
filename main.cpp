#include "Chess.h"

#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

void displayMenu();
void playGame();
void displayHelp();
void gotoxy(short int x, short int y) {
  COORD screen = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), screen);
}

void setColor(int c) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); }


int main()
{
  do {
    system("cls");
    displayMenu();
  } while (true);
  _getch();
  return 0;
}

void displayMenu() {
  setColor(8);
  cout << "          CCCCCC   HHH     HHH   EEEEEEEEE    SSSSSSS    SSSSSSS            o        o  o  o" << endl;
  Sleep(80);
  setColor(8);
  cout << "         CCCCCCC   HHH     HHH   EEEEEEEEE   SSSSSSSS   SSSSSSSS          ooooo      ooooooo" << endl;
  Sleep(80);
  setColor(15);
  cout << "        CCC        HHH     HHH   EEE         SSS        SSS               ooooo      ooooooo" << endl;
  Sleep(80);
  setColor(15);
  cout << "        CCC        HHH     HHH   EEE         SSS        SSS                ooo         ooo  " << endl;
  Sleep(80);
  setColor(15);
  cout << "        CCC        HHHHHHHHHHH   EEEEEEEE    SSSSSSS    SSSSSSS            ooo         ooo  " << endl;
  Sleep(80);
  setColor(15);
  cout << "        CCC        HHHHHHHHHHH   EEEEEEEE     SSSSSSS    SSSSSSS           ooo         ooo  " << endl;
  Sleep(80);
  setColor(15);
  cout << "        CCC        HHH     HHH   EEE              SSS        SSS           ooo         ooo  " << endl;
  Sleep(80);
  setColor(15);
  cout << "        CCC        HHH     HHH   EEE              SSS        SSS           ooo         ooo  " << endl;
  Sleep(80);
  setColor(8);
  cout << "         CCCCCCC   HHH     HHH   EEEEEEEEE   SSSSSSSS   SSSSSSSS         ooooooo     ooooooo" << endl;
  Sleep(80);
  setColor(8);
  cout << "          CCCCCC   HHH     HHH   EEEEEEEEE   SSSSSSS    SSSSSSS          OOOOOOO     OOOOOOO" << endl;
  gotoxy(1, 28);
  cout << "Copyright 2016";
  int choice = -1;
  setColor(15);
  gotoxy(40, 12);
  Sleep(80);
  cout << "1 - Play";
  gotoxy(40, 13);
  Sleep(80);
  cout << "2 - Help";
  gotoxy(40, 14);
  Sleep(80);
  cout << "3 - Exit";
  gotoxy(40, 16);
  cout << "Your Choice: ";
  cin >> choice;
  if (choice == 1) {
    system("cls");
    playGame();
  } else if (choice == 2) {
    system("cls");
    displayHelp();
  } else if (choice == 3) {
    exit(0);
  } else {
    gotoxy(40, 17);
    cout << "Invalid\n";
    gotoxy(40, 18);
    cout << "Press any key to continue...";
    _getch();
  }
}

void playGame() {
  Chess *chess = new Chess;//creating an object
  chess->displayBoard();//displaying board for first time
  char move[5] = { '\0' };//hold input to move piece
  do /*terminate on checkmate*/ {
    do /*continue if input is invalid*/ {
      if (chess->getTurn()) /*checking which players turn*/ {
        cout << "Player1's Move: ";
      } else {
        cout << "Player2's Move: ";
      }
      cin >> move;
      if ((toupper(move[0]) == 'E') && (toupper(move[1]) == 'X') 
        && (toupper(move[2]) == 'I') && (toupper(move[3]) == 'T')) /*if player want to surrender*/ {
        if (chess->getTurn()) {
          system("cls");
          cout << "Winner: Player2\n";
          cout << "Press any key to continue...";
          _getch();
          return;
        } else { 
          system("cls");
          cout << "Winner: Player1\n";
          cout << "Press any key to continue...";
          _getch();
          return;
        }
      }
      chess->setInput(move);
      chess->setCoordinatesOfPiece();
    } while (chess->inputValidation());
    if (chess->getTurn()) /*player1's moves*/ {
      if (chess->getPieceLocation() == 'P' && chess->isPawnValid()) {
        chess->stepsOfPlayer1();
      } else if (chess->getPieceLocation() == 'R' && chess->isRookValid()) {
        chess->stepsOfPlayer1();
      } else if (chess->getPieceLocation() == 'N' && chess->isKnightValid()) {
        chess->stepsOfPlayer1();
      } else if (chess->getPieceLocation() == 'B' && chess->isBishopValid()) {
        chess->stepsOfPlayer1();
      } else if (chess->getPieceLocation() == 'Q' && chess->isQueenValid()) {
        chess->stepsOfPlayer1();
      } else if (chess->getPieceLocation() == 'K' && chess->isKingValid()) {
        chess->stepsOfPlayer1();
      } else {
        cout << "Illegal Move!!!\n";
      }
    } else /*player2's move*/ {
      if (chess->getPieceLocation() == 'p' && chess->isPawnValid()) {
        chess->stepsOfPlayer2();
      } else if (chess->getPieceLocation() == 'r' && chess->isRookValid()) {
        chess->stepsOfPlayer2();
      } else if (chess->getPieceLocation() == 'n' && chess->isKnightValid()) {
        chess->stepsOfPlayer2();
      } else if (chess->getPieceLocation() == 'b' && chess->isBishopValid()) {
        chess->stepsOfPlayer2();
      } else if (chess->getPieceLocation() == 'q' && chess->isQueenValid()) {
        chess->stepsOfPlayer2();
      } else if (chess->getPieceLocation() == 'k' && chess->isKingValid()) {
        chess->stepsOfPlayer2();
      } else {
        cout << "Illegal Move!!!\n";
      }
    }
  } while (chess->checkmate());
  system("cls");
  if (chess->gameWon()) /*checking whick player has won*/ {
    cout << "Winner: Player1\n";
    cout << "Press any key to continue...";
    _getch();
  } else {
    cout << "Winner: Player2\n";
    cout << "Press any key to continue...";
    _getch();
  }
  delete chess;
}

void displayHelp() {
  cout << "\t\t\t\tHOW TO PLAY\n\n";
  cout << "\t\t\tINTRODUCTION\n\n";
  cout << "1.The Board is divided into 8 rows and 8 columns.\n";
  cout << "2.Columns are labeled with alphabets.\n";
  cout << "3.Rows are labeled with numbers.\n";
  cout << "4.It is a two players game.\n\n";
  cout << "\t\t\tHOW TO MAKE A MOVE\n\n";
  cout << "1.First enter the cell address to move from\n then enter the cell address to move to. For example,\n";
  cout << " if the cell's address to move from is E1\n and the address to move to is E4 you will write E1E4 or simply e1e4.\n";
  cout << "2.You can write address in both uppercase or lowercase format.\n\n";
  cout << "\t\t\tMOVES\n\n";
  cout << "1.It has original Chess Game's rules.\n";
  cout << "2.Any invalid move will give an error.\n";
  cout << "3.Moves are as follows :\n";
  cout << "->King(k) : Can move to only one box around it.\n";
  cout << "->Queen(q) : Can move through whole board.\n";
  cout << "->Rook(r) : Can move straight line from front and side.\n";
  cout << "->Bishop(b) : Can move through diagonals.\n";
  cout << "->Pawn(p) : Can move 2 cells from front at start of game and one afterwards.\n";
  cout << "->Knight(n) : Can move in L shape in any direction.(2 cells from front and 1 from side.)\n\n\n";
  cout << "Developed By :\nSher Ali BCSF15M012\nM UMER FAROOQ BCSF15M025\n";
  cout << "Press any key to continue...";
  _getch();
}
