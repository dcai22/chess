#include <optional>
#include <iostream>

#include "game.h"
#include "helper.h"
#include "move.h"

Game::Game()
: board_(Board())
{}

auto Game::processMove(const Move& move) -> bool {
    if (isValidMove(move)) {
        board_.executeMove(move, ++numMoves_);
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

auto Game::isValidMove(const Move& move) const -> bool {
    auto movingPiece = board_.pieceAt(move.from).lock();

    if (!movingPiece) {
        std::cout << "There is no piece there!" << std::endl;
        return false;
    }

    if (movingPiece->getColour() != colourToMove_) {
        std::cout << "That piece does not belong to you!" << std::endl;
        return false;
    }
    
    if (move.from == move.to) {
        std::cout << "Start and end square cannot be the same" << std::endl;
        return false;
    }

    auto intendedMoveType = movingPiece->deduceMoveType(board_, move);
    switch(intendedMoveType) {
        case MoveType::None:
            std::cout << "That piece cannot move there!" << std::endl;
            return false;

        // TODO
        case MoveType::Move:
            return true;

        case MoveType::Capture:
            return true;

        case MoveType::KingsideCastle:
            return true;

        case MoveType::QueensideCastle:
            return true;

        case MoveType::EnPassant:
            return true;
    }

    // auto target = board.pieceAt(move.to).lock();

    return true;
}
