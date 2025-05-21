#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
#include <vector>
#include <memory>
#include <string>

#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "constants.h"

class Board {
 private:
    std::unique_ptr<Piece> board_[Constants::BOARD_SIZE][Constants::BOARD_SIZE]; // e.g. e2 corresponds to board_[3][1] because 'e' -> 3 and '2' -> 1
    bool whiteHasKing = true;
    bool blackHasKing = true;

    auto updateHasKing() -> void;

 public:
    Board();

    auto processMove(const std::string& move) -> bool;
    auto printState() const -> void;
    auto hasEnded() const -> bool;
    auto getWinner() const -> std::optional<PieceColour>;

    static auto isValidSquare(const std::string& str) -> bool;
};

#endif // BOARD_H
