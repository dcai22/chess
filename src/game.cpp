#include <optional>

#include "game.h"
#include "helper.h"
#include "move.h"

Game::Game()
: board_(Board())
{}

auto Game::processMove(const Move& move) -> bool {
    if (moveValidator_.isValidMove(board_, move, colourToMove_)) {
        board_.processMove(move);
        switch (colourToMove_) {
            case PieceColour::White:
                colourToMove_ = PieceColour::Black;
                break;

            case PieceColour::Black:
                colourToMove_ = PieceColour::White;
                break;
        }
        return true;
    } else {
        return false;
    }
}

auto Game::printBoard() const -> void {
    board_.printState();
}

auto Game::getWinner() const -> std::optional<PieceColour> {
    return board_.getWinner();
}

auto Game::hasEnded() const -> bool {
    return board_.hasEnded();
}

auto Game::getColourToMove() const -> PieceColour {
    return colourToMove_;
}
