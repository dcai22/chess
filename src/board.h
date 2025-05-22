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
    bool whiteHasKing_ = true;
    bool blackHasKing_ = true;

    auto updateHasKing() -> void;
    auto getKingSquare(const PieceColour& colour) const -> std::optional<Square>;
    
    public:
    Board();
    
    auto executeMove(const Move& move, const MoveType& moveType) -> void;
    auto processMove(const Move& move, const MoveType& moveType, const int moveNum) -> void;
    auto printState() const -> void;
    auto hasEnded() const -> bool;
    auto getWinner() const -> std::optional<PieceColour>;
    auto pieceAt(const Square& square) const -> std::weak_ptr<Piece>;
    auto isSquareAttacked(const Square& square, const PieceColour& byColour) -> bool;
    auto isInCheck(const PieceColour& playerColour) -> bool;
};
