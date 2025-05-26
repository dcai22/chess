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
    int startingRow_;
    bool lastMoved_ = 0;

    protected:
    Piece(const double value, const char symbol, const PieceColour& colour, const int startingRow);

    [[nodiscard]] virtual auto getStartingRow(const PieceColour& colour) const noexcept -> int;
    
    public:
    [[nodiscard]] auto getValue() const noexcept -> double;
    [[nodiscard]] auto getSymbol() const noexcept -> char;
    [[nodiscard]] auto getDisplaySymbol() const noexcept -> char;
    [[nodiscard]] auto getColour() const noexcept -> PieceColour;
    [[nodiscard]] auto getLastMoved() const noexcept -> int;
    [[nodiscard]] auto hasMoved() const noexcept -> bool;
    [[nodiscard]] auto isKing() const noexcept ->  bool;
    [[nodiscard]] auto isQueen() const noexcept ->  bool;
    [[nodiscard]] auto isRook() const noexcept ->  bool;
    [[nodiscard]] auto isBishop() const noexcept ->  bool;
    [[nodiscard]] auto isKnight() const noexcept ->  bool;
    [[nodiscard]] auto isPawn() const noexcept ->  bool;
    [[nodiscard]] auto isColour(const PieceColour& colour) const noexcept -> bool;
    [[nodiscard]] auto getStartingRow() const noexcept -> int;

    auto setLastMoved(const int& moveNum) noexcept -> void;

    [[nodiscard]] virtual auto getAttackedSquares(const Board& board, const Square& from) const -> std::vector<Square>;
    [[nodiscard]] auto isAttack(const Board& board, const Move& move) const -> bool;
    [[nodiscard]] virtual auto getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> = 0;

    virtual ~Piece() = default;
};
