#ifndef PIECE_H
#define PIECE_H

class Piece {
 private:
    double value;
    char symbol;
   
 protected:
    Piece(double value, char symbol);

 public:
    auto getValue() -> double;
    auto getSymbol() -> char;
};

#endif // PIECE_H
