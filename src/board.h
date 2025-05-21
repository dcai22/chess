#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include <string>

#include "pieces/piece.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "constants.h"
#include "move.h"

class Board {
 private:
    std::unique_ptr<Piece> board_[Constants::BOARD_SIZE][Constants::BOARD_SIZE]; // board_[row][col], row starts from '1', col starts from 'a', e.g. "e2" -> board_[1][3]
    bool whiteHasKing_ = true;
    bool blackHasKing_ = true;

    auto updateHasKing() -> void;

 public:
    Board();

    auto processMove(const Move& move) -> void;
    auto printState() const -> void;
    auto hasEnded() const -> bool;
    auto getWinner() const -> std::optional<PieceColour>;
};
