#include <optional>
#include <iostream>

#include "game.h"
#include "helper.h"
#include "move.h"

Game::Game()
: board_(Board())
{}

auto Game::processMove(const Move& move) -> bool {
    const auto moveType = validateMove(move);
    if (moveType == MoveType::None) {
        return false;
    } else {
        moves_.push_back(move);
        board_.processMove(move, moveType, static_cast<int>(moves_.size()) + 1);
        colourToMove_ = oppositeColour(colourToMove_);
        return true;
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

auto Game::validateMove(const Move& move) const -> MoveType {
    auto movingPiece = board_.pieceAt(move.from).lock();

    if (!movingPiece) {
        std::cout << "There is no piece there!" << std::endl;
        return MoveType::None;
    }

    if (movingPiece->getColour() != colourToMove_) {
        std::cout << "That piece does not belong to you!" << std::endl;
        return MoveType::None;
    }
    
    if (move.from == move.to) {
        std::cout << "Start and end square cannot be the same" << std::endl;
        return MoveType::None;
    }

    auto intendedMoveType = movingPiece->deduceMoveType(board_, move);
    switch(intendedMoveType) {
        case MoveType::None:
            std::cout << "That piece cannot move there!" << std::endl;
            return MoveType::None;

        case MoveType::Move:
            break;

        case MoveType::Capture:
            break;

        case MoveType::KingsideCastle:
            break;

        case MoveType::QueensideCastle:
            break;

        case MoveType::EnPassant:
            if (!validateEnPassant(move)) {
                std::cout << "Invalid en-passant" << std::endl;
                return MoveType::None;
            }
    }

    auto dupBoard = board_;
    dupBoard.executeMove(move, intendedMoveType);
    if (dupBoard.isInCheck(colourToMove_)) {
        std::cout << "Move would result in check" << std::endl;
        return MoveType::None;
    }

    return intendedMoveType;
}

auto Game::validateEnPassant(const Move& move) const -> bool {
    if (moves_.empty()) {
        return false;
    }

    const auto enPassantSquare = Square(move.from.row, move.to.col);
    const auto lastMove = moves_[moves_.size() - 1];
    if (enPassantSquare == lastMove.to && abs(lastMove.to.row - lastMove.from.row) == 2) {
        return true;
    } else {
        return false;
    }
}
