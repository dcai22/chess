#include <string>
#include <optional>

#include "game.h"
#include "helper.h"

Game::Game()
: board_(Board())
{}

auto Game::processMove(const std::string& move) -> bool {
    if (board_.processMove(move)) {
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

auto Game::isValidMove(std::string move) -> bool {
    auto tokens = splitByWhitespace(move);
    if (tokens.size() != 2) {
        return false;
    }

    for (const auto& token : tokens) {
        if (!Board::isValidSquare(token)) {
            return false;
        }
    }

    return true;
}
