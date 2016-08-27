#include "Chess.h"

#include <iostream>
using namespace std;

Chess::Chess() { setBoard(); }

void Chess::setBoard() {
  //for black pieces
  chess[0][0] = chess[0][7] = 'r';//rooks
  chess[0][1] = chess[0][6] = 'n';//knights
  chess[0][2] = chess[0][5] = 'b';//bishops
  chess[0][3] = 'q';//queen
  chess[0][4] = 'k';//king
  chess[1][0] = chess[1][1] = chess[1][2] = chess[1][3] = chess[1][4]
    = chess[1][5] = chess[1][6] = chess[1][7] = 'p';
  //for white pieces
  chess[7][0] = chess[7][7] = 'R';//rooks
  chess[7][1] = chess[7][6] = 'N';//knights
  chess[7][2] = chess[7][5] = 'B';//bishop
  chess[7][3] = 'Q';//queen
  chess[7][4] = 'K';//king
  chess[6][0] = chess[6][1] = chess[6][2] = chess[6][3] = chess[6][4]
    = chess[6][5] = chess[6][6] = chess[6][7] = 'P';
  //remaining board
  for (int i = 2; i < 6; i++) {
    for (int j = 0; j < 8; j++) {
      chess[i][j] = ' ';
    }
  }
  //captured piece will be stored in this matrix
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 8; j++) {
      capturedByWhite[i][j] = ' ';
      capturedByBlack[i][j] = ' ';
    }
  }
  player1 = player2 = false;
  turn = true;
}

void Chess::displayBoard() {
  cout << "For Surrender type exit\n";
  cout << "Captured By Player1\t\t\tCaptured By Player2\n";
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 8; j++) {
      cout << capturedByWhite[i][j] << " ";
    }
    cout << "\t\t\t";
    for (int k = 0; k < 8; k++) {
      cout << capturedByBlack[i][k] << " ";
    }
    cout << "\n";
  }
  cout << "\n      ";
  for (char cols = 'A'; cols < 'I'; cols++) {//display columns coordinates
    cout << cols << "      ";
  }
  cout << "\n";
  for (int a = 0, rows = 8; a < 8; a++) {//displaying pieces in boxes
    cout << "   ";
    for (int b = 0; b < 8; b++) {
      cout << char(218) << char(196) << char(196) << char(196) << char(196) << char(196) << char(191);
    }
    cout << '\n';
    cout << rows << "  ";//displaying rows coordinates
    for (int b = 0; b < 8; b++) {
      cout << char(179) << "  " << chess[a][b] << "  " << char(179);//displaying piece
    }
    cout << "  " << rows--;
    cout << "\n   ";
    for (int b = 0; b < 8; b++) {
      cout << char(192) << char(196) << char(196) << char(196) << char(196) << char(196) << char(217);
    }
    cout << '\n';
  }
  cout << "      ";
  for (char cols = 'A'; cols < 'I'; cols++) {//display columns coordinates
    cout << cols << "      ";
  }
  cout << "\n";
}

void Chess::setInput(char input[]) {
  for (int i = 0; i < 5; i++) { this->input[i] = input[i]; }
}

void Chess::setTurn(bool turn) { this->turn = turn; }

bool Chess::getTurn() const { return this->turn; }

bool Chess::inputValidation() {
  if ((input[0] >= 'A' && input[0] <= 'H') && (input[1] >= '0' && input[1] <= '7')
    && (input[2] >= 'A' && input[2] <= 'H') && (input[3] >= '0' && input[3] <= '7')) /*input in 8X8*/ {
      //checking player does not capture own piece
    if ((turn && (getPieceLocation() == 'P' || getPieceLocation() == 'B' 
      || getPieceLocation() == 'R' || getPieceLocation() == 'N' || getPieceLocation() == 'Q' || getPieceLocation() == 'K') 
      && (getPieceDestination() == 'p' || getPieceDestination() == 'b' || getPieceDestination() == 'r'
        || getPieceDestination() == 'n' || getPieceDestination() == 'q' || getPieceDestination() == 'k' || getPieceDestination() == ' ')) ||
      (!turn && (getPieceLocation() == 'p' || getPieceLocation() == 'b' || getPieceLocation() == 'r'
        || getPieceLocation() == 'n' || getPieceLocation() == 'q' || getPieceLocation() == 'k') 
        && (getPieceDestination() == 'P' || getPieceDestination() == 'B' || getPieceDestination() == 'R'
          || getPieceDestination() == 'N' || getPieceDestination() == 'Q' || getPieceDestination() == 'K' || getPieceDestination() == ' '))) {
      return false;
    } else {
      cout << "Illegal Move!!!\n";
      return true;
    }
  } else {
    cout << "Illegal Move!!!\n";
    return true;
  }
}

void Chess::setCoordinatesOfPiece() {
  input[0] = toupper(input[0]);
  input[1] = toupper(input[1]) - 1;
  input[2] = toupper(input[2]);
  input[3] = toupper(input[3]) - 1;
  input[4] = input[4];
  j1 = input[0] - 65;
  i1 = 7 - (input[1] - 48);
  j2 = input[2] - 65;
  i2 = 7 - (input[3] - 48);
}

char Chess::getPieceLocation() const { return chess[i1][j1]; }

char Chess::getPieceDestination() const { return chess[i2][j2]; }

void Chess::movePiece() {
  chess[i2][j2] = chess[i1][j1];
  chess[i1][j1] = ' ';
}

bool Chess::isPawnValid() {
  //first jump of pawn can be of two boxes 
  if ((chess[i1][j1] == 'P' && i1 == 6 && i2 == 4 && j1 == j2 && chess[i1 - 1][j1] == ' ' && chess[i1 - 2][j1] == ' ')//white pawn
    || (chess[i1][j1] == 'p' && i1 == 1 && i2 == 3 && j1 == j2 && chess[i1 + 1][j1] == ' ' && chess[i1 + 2][j1] == ' '))/*black pawn*/ {
    return true;
    //every straight jump except first
  } else if ((chess[i1][j1] == 'P' && i2 == (i1 - 1) && j1 == j2 && chess[i2][j2] == ' ')//white pawn
    || (chess[i1][j1] == 'p' && i2 == (i1 + 1) && j1 == j2 && chess[i2][j2] == ' ')) /*black pawn*/ {
    return true;
    //white pawn reaches other side of board
  } else if (chess[i1][j1] == 'P' && (i2 == 0 && j1 == j2 && chess[i2][j2] == ' ')//move straight
    || (i2 == 0 && (j2 == (j1 + 1) || j2 == (j1 - 1)) && (chess[0][j1 + 1] != ' ' || chess[0][j1 - 1] != ' ')))/*move diagonal*/ {
    //pawn is to be converted to any one of queen, rook, knight or bishop
    char choice;
    do {//asking for conversion 
      cout << "Choice to convert Pawn: ";
      cin >> choice;
      if (toupper(choice) == 'Q') {
        chess[i1][j1] = 'Q';
      } else if (toupper(choice) == 'R') {
        chess[i1][j1] = 'R';
      } else if (toupper(choice) == 'N') {
        chess[i1][j1] = 'N';
      } else if (toupper(choice) == 'B') {
        chess[i1][j1] = 'B';
      } else {
        cout << "Invalid!!!\n";
      }
    } while (toupper(choice) != 'Q' && toupper(choice) != 'R' && toupper(choice) != 'N' && toupper(choice) != 'B');
    return true;
    //black pawn reaches other side of board
  } else if (chess[i1][j1] == 'p' && (i2 == 7 && j1 == j2 && chess[i2][j2] == ' ')//move straight
    || (i2 == 7 && (j2 == (j1 + 1) || j2 == (j1 - 1)) && (chess[7][j1 + 1] != ' ' || chess[7][j1 - 1] != ' ')))/*move diagonal*/ {
    //if black pawn is at the opposite side then it is to be converted to any one of queen, rook, knight or bishop
    char choice;
    do {//asking for conversion 
      cout << "Choice to convert Pawn: ";
      cin >> choice;
      if (tolower(choice) == 'q') {
        chess[i1][j1] = 'q';
      } else if (tolower(choice) == 'r') {
        chess[i1][j1] = 'r';
      } else if (tolower(choice) == 'n') {
        chess[i1][j1] = 'n';
      } else if (tolower(choice) == 'b') {
        chess[i1][j1] = 'b';
      } else {
        cout << "Invalid!!!\n";
      }
    } while (tolower(choice) != 'q' && tolower(choice) != 'r' && tolower(choice) != 'n' && tolower(choice) != 'b');
    return true;
    //capturing opponent's piece if present at diagonal
  } else if (((chess[i1][j1] == 'P' && i2 == (i1 - 1) && (j2 == (j1 + 1) || j2 == (j1 - 1))) && (chess[i2][j1 + 1] != ' ' || chess[i2][j1 - 1] != ' '))
    || ((chess[i1][j1] == 'p' && i2 == (i1 + 1) && (j2 == (j1 + 1) || j2 == (j1 - 1))) && (chess[i2][j1 + 1] != ' ' || chess[i2][j1 - 1] != ' '))) {
    return true;
  } else {
    return false;
  }
}

bool Chess::isBishopValid() {
  if (i1 != i2 && j1 != j2) {
    if (i2 < i1 && j2 > j1) {//upper right diagonal for white and lower left for black 
      for (int i = i1 - 1, j = j1 + 1; i >= i2 && j <= j2; i--, j++) {
        if (i > i2 && j < j2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (i == i2 && j == j2) {//reached the destination
          return true;
        }
      }
      return false;
    } else if (i2 < i1 && j1 > j2) {//upper left diagonal for white and lower right for black
      for (int i = i1 - 1, j = j1 - 1; i >= i2 && j >= j2; i--, j--) {
        if (i > i2 && j > j2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (i == i2 && j == j2) {//reached the destination
          return true;
        }
      }
      return false;
    } else if (i2 > i1 && j2 > j1) {//lower right diagonal for white and upper left for black
      for (int i = i1 + 1, j = j1 + 1; i <= i2 && j <= j2; i++, j++) {
        if (i > i2 && j > j2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (i == i2 && j == j2) {//reached the destination
          return true;
        }
      }
      return false;
    } else if (i2 > i1 && j2 > j1) {//lower left diagonal for white and upper right for black
      for (int i = i1 + 1, j = j1 - 1; i <= i2 && j >= j2; i++, j--) {
        if (i < i2 && j > j2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (i == i2 && j == j2) {//reached the destination
          return true;
        }
      }
      return false;
    }
  } else {
    return false;
  }
}

bool Chess::isRookValid() {
  if ((i1 == i2 && (j1 != j2)) || (j1 == j2 && (i1 != i2))) {//if location and destination is same
    if (i2 < i1 && j1 == j2) {//upper vertical check for white and lower for black 
      for (int i = i1 - 1, j = j1; i >= i2; i--) {
        if (i > i2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (i == i2) {//reached the destination
          return true;
        }
      }
      return false;
    } else if (i2 > i1 && j1 == j2) {//lower vertical check for white and upper for black
      for (int i = i1 + 1, j = j1; i <= i2; i++) {
        if (i < i2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (i == i2) {//reached the destination
          return true;
        }
      }
      return false;
    } else if (i1 == i1 && j1 < j2) {//right horizontal check for white and left for black
      for (int i = i1, j = j1 + 1; j <= j2; j++) {
        if (j < j2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (j == j2) {//reached the destination
          return true;
        }
      }
      return false;
    } else if (i1 == i2, j2 < j1) {//left horizontal check for white and right for black
      for (int i = i1, j = j1 - 1; j >= j2; j--) {
        if (j > j2 && chess[i][j] != ' ') {//something else encounters before reaching destination
          return false;
        } else if (j == j2) {//reached the destination
          return true;
        }
      }
      return false;
    }
  } else {
    return false;
  }
}

bool Chess::isKnightValid() {
  if ((i2 == (i1 - 2) && j2 == (j1 + 1)) || (i2 == (i1 - 2) && j2 == (j1 - 1))//check upward movement for white and downward for black
    || (i2 == (i1 + 2) && j2 == (j1 + 1)) || (i2 == (i1 + 2) && j2 == (j1 - 1))//check downward movement for white and upward for black
    || (i2 == (i1 - 1) && j2 == (j1 + 2)) || (i2 == (i1 + 1) && j2 == (j1 + 2))//check rightward movement for white and leftward for black
    || (i2 == (i1 - 1) && j2 == (j1 - 2)) || (i2 == (i1 + 1) && j2 == (j1 - 2)))/*check leftward movement for white and rightward for black*/ {
    return true;
  } else {
    return false;
  }
}

bool Chess::isQueenValid() {
  if (isBishopValid() || isRookValid())/*queen has bishop and rook moves*/ {
    return true;
  } else {
    return false;
  }
}

bool Chess::isKingValid() {
  if (((i2 == (i1 - 1) && j1 == j2) || (i2 == (i1 + 1) && j1 == j2)//up and down check
    || (i2 == i1 && j2 == (j1 + 1)) || (i2 == i1 && j2 == (j1 - 1))//right and left check
    || (i2 == (i1 - 1) && j2 == (j1 + 1)) || (i2 == (i1 + 1) && j2 == (j1 + 1))//upper and lower right diagonal check
    || (i2 == (i1 - 1) && j2 == (j1 - 1)) || (i2 == (i1 + 1) && j2 == (j1 - 1)))) /*upper and lower left diagonal check*/ {
    return true;
  } else {
    return false;
  }
}

void Chess::setCapturedPiecesByWhite(const char & piece, const int & i, const int & j) { capturedByWhite[i][j] = piece; }

void Chess::setCapturedPieceByBlack(const char & piece, const int & i, const int & j) { capturedByBlack[i][j] = piece; }

void Chess::stepsOfPlayer1() {
  static int i = 0, j = 0;
  if (getPieceDestination() != ' ') {
    setCapturedPiecesByWhite(getPieceDestination(), i, j);
    j++;
    if (j > 7) {
      i++;
      j = 0;
    }
  }
  setTurn(false);
  movePiece();
  system("cls");
  displayBoard();
}

void Chess::stepsOfPlayer2() {
  static int i = 0, j = 0;
  if (getPieceDestination() != ' ') {
    setCapturedPieceByBlack(getPieceDestination(), i, j);
    j++;
    if (j > 7) {
      i++;
      j = 0;
    }
  }
  setTurn(true);
  movePiece();
  system("cls");
  displayBoard();
}

bool Chess::checkmate() /*if both kings are present on board then help in continuing game*/ {
  player1 = player2 = false;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (chess[i][j] == 'K') {
        player1 = true;
      } else if (chess[i][j] == 'k') { 
        player2 = true;
      }
    }
  }
  if (player1 && player2) {
    return true;
  } else { 
    return false;
  }
}

bool Chess::gameWon() {
  if (player1) {
    return true;
  } else { 
    return false;
  }
}

Chess::~Chess() { }
