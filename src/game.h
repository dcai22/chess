#ifndef GAME_H
#define GAME_H

#include <optional>
#include <string>

#include "board.h"
#include "types.h"

class Game {
 private:
    Board board;
    std::optional<PieceColour> winner = std::nullopt;
    bool hasEnded = false;
    PieceColour colourToMove = PieceColour::White;

 public:
    Game();

    auto processMove(const std::string& move) -> bool;
    auto printBoard() const -> void;

    auto getWinner() const -> std::optional<PieceColour>;
    auto getHasEnded() const -> bool;
    auto getColourToMove() const -> PieceColour;

    static auto isValidMove(std::string move) -> bool;
};

#endif // GAME_H
