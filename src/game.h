#pragma once

#include <optional>

#include "board.h"
#include "types.h"

class Game {
 private:
    Board board_;
    PieceColour colourToMove_ = PieceColour::White;
    std::vector<Move> moves_ = std::vector<Move>();

    auto validateMove(const Move& move) const -> MoveType;
    auto validateEnPassant(const Move& move) const -> bool;
    auto validateCastle(const Move& move) const -> bool;

 public:
    Game();

    auto processMove(const Move& move) -> bool;
    auto printBoard() const -> void;

    auto getWinner() const -> std::optional<PieceColour>;
    auto hasEnded() const -> bool;
    auto getColourToMove() const -> PieceColour;
};
