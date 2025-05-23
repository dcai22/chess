#pragma once

#include <vector>

#include "../types.h"
#include "../square.h"

// forward declarations
class Board;
class Move;
struct LegalMove;

class Piece {
 private:
    double value_;
    char symbol_;
    PieceColour colour_;
    bool lastMoved_ = 0;

 protected:
    Piece(const double value, const char symbol, const PieceColour colour);

    public:
    auto getValue() const -> double;
    auto getSymbol() const -> char;
    auto getDisplaySymbol() const -> char;
    auto getColour() const -> PieceColour;
    auto getLastMoved() const -> int;
    auto hasMoved() const -> bool;
    auto isKing() const ->  bool;
    auto isQueen() const ->  bool;
    auto isRook() const ->  bool;
    auto isBishop() const ->  bool;
    auto isKnight() const ->  bool;
    auto isPawn() const ->  bool;
    auto isColour(const PieceColour& colour) const -> bool;
    virtual auto getStartingRow() const -> int = 0;

    auto setLastMoved(const int& moveNum) -> void;

    virtual auto getAttackedSquares(const Board& board, const Square& from) const -> std::vector<Square>;
    auto isAttack(const Board& board, const Move& move) const -> bool;
    virtual auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> = 0;

    virtual ~Piece() = default;
};
