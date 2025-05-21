#ifndef GAME_H
#define GAME_H

#include <optional>
#include <string>

#include "board.h"
#include "types.h"

class Game {
 private:
    Board board_;
    PieceColour colourToMove_ = PieceColour::White;

 public:
    Game();

    auto processMove(const std::string& move) -> bool;
    auto printBoard() const -> void;

    auto getWinner() const -> std::optional<PieceColour>;
    auto hasEnded() const -> bool;
    auto getColourToMove() const -> PieceColour;

    static auto isValidMove(std::string move) -> bool;
};

#endif // GAME_H
