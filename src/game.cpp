#include <string>
#include <optional>

#include "game.h"
#include "helper.h"

Game::Game()
: board(Board())
{}

auto Game::processMove(const std::string& move) -> bool {
    if (this->board.processMove(move)) {
        switch (this->colourToMove) {
            case PieceColour::White:
                this->colourToMove = PieceColour::Black;
                break;
            
            case PieceColour::Black:
                this->colourToMove = PieceColour::White;
                break;

            default:
                break;
        }

        return true;
    } else {
        return false;
    }
}

auto Game::printBoard() const -> void {
    this->board.printState();
}

auto Game::getWinner() const -> std::optional<PieceColour> {
    return this->winner;
}

auto Game::getHasEnded() const -> bool {
    return this->hasEnded;
}

auto Game::getColourToMove() const -> PieceColour {
    return this->colourToMove;
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
