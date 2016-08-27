#ifndef CHESS_H
#define CHESS_H

class Chess {
  char chess[8][8];
  char capturedByWhite[2][8];
  char capturedByBlack[2][8];
  char input[5];
  bool player1, player2, turn;
  int i1, j1;
  int i2, j2;
public:
  Chess();
  void setBoard();
  void displayBoard();
  void setInput(char[]);
  void setTurn(bool turn);
  bool getTurn() const ;
  bool inputValidation();
  void setCoordinatesOfPiece();
  char getPieceLocation() const ;
  char getPieceDestination() const ;
  void movePiece();
  bool isPawnValid();
  bool isBishopValid();
  bool isRookValid();
  bool isKnightValid();
  bool isQueenValid();
  bool isKingValid();
  void setCapturedPiecesByWhite(const char & piece, const int & i, const int & j);
  void setCapturedPieceByBlack(const char & piece, const int & i, const int & j);
  void stepsOfPlayer1();
  void stepsOfPlayer2();
  bool checkmate();
  bool gameWon();
  ~Chess();
};

#endif // !CHESS_H