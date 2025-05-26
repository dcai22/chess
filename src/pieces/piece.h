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
    [[nodiscard]] auto getValue() const -> double;
    [[nodiscard]] auto getSymbol() const -> char;
    [[nodiscard]] auto getDisplaySymbol() const -> char;
    [[nodiscard]] auto getColour() const -> PieceColour;
    [[nodiscard]] auto getLastMoved() const -> int;
    [[nodiscard]] auto hasMoved() const -> bool;
    [[nodiscard]] auto isKing() const ->  bool;
    [[nodiscard]] auto isQueen() const ->  bool;
    [[nodiscard]] auto isRook() const ->  bool;
    [[nodiscard]] auto isBishop() const ->  bool;
    [[nodiscard]] auto isKnight() const ->  bool;
    [[nodiscard]] auto isPawn() const ->  bool;
    [[nodiscard]] auto isColour(const PieceColour& colour) const -> bool;
    [[nodiscard]] virtual auto getStartingRow() const -> int = 0;

    auto setLastMoved(const int& moveNum) -> void;

    [[nodiscard]] virtual auto getAttackedSquares(const Board& board, const Square& from) const -> std::vector<Square>;
    [[nodiscard]] auto isAttack(const Board& board, const Move& move) const -> bool;
    [[nodiscard]] virtual auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> = 0;

    virtual ~Piece() = default;
};
