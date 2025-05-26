#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include <string>

#include "pieces/piece.h"
#include "constants.h"
#include "board.h"
#include "move.h"

// forward declarations
class Move;
class Square;

class Board {
 private:
    std::shared_ptr<Piece> board_[Constants::BOARD_SIZE][Constants::BOARD_SIZE]; // board_[row][col], row starts from '1', col starts from 'a', e.g. "e2" -> board_[1][3]
    [[nodiscard]] auto getKingSquare(const PieceColour& colour) const -> std::optional<Square>;

    public:
    Board();

    auto executeMove(const LegalMove& legalMove) -> void;
    auto processMove(const LegalMove& legalMove, const int moveNum) -> void;
    auto printState() const -> void;
    [[nodiscard]] auto pieceAt(const Square& square) const -> std::weak_ptr<Piece>;
    [[nodiscard]] auto isSquareAttacked(const Square& square, const PieceColour& byColour) const -> bool;
    [[nodiscard]] auto isInCheck(const PieceColour& playerColour) const -> bool;
    [[nodiscard]] auto getPositionString() const -> std::string;
    [[nodiscard]] auto hasInsufficientMaterial() const -> bool;

    [[nodiscard]] auto isBigPawnPush(const Move& move) const -> bool;
};
