#pragma once

#include <optional>

#include "board.h"
#include "types.h"
#include "move_validator.h"

class Game {
 private:
    Board board_;
    PieceColour colourToMove_ = PieceColour::White;
    MoveValidator moveValidator_ = MoveValidator();

 public:
    Game();

    auto processMove(const Move& move) -> bool;
    auto printBoard() const -> void;

    auto getWinner() const -> std::optional<PieceColour>;
    auto hasEnded() const -> bool;
    auto getColourToMove() const -> PieceColour;
};
