#include <optional>
#include <iostream>

#include "game.h"
#include "helper.h"
#include "move.h"

Game::Game() {
    updateLegalMoves();
}

auto Game::processMove(const Move& move) -> bool {
    const auto moveType = getMoveType(move);
    if (moveType == MoveType::None) {
        std::cout << "Illegal move" << std::endl;
        return false;
    } else {
        if (board_.isBigPawnPush(move)) {
            auto targetRow = (move.from.row + move.to.row) / 2;
            auto targetCol = move.from.col;
            enPassantTarget_ = Square(targetRow, targetCol);
        } else {
            enPassantTarget_ = std::nullopt;
        }

        moves_.push_back(move);
        board_.processMove(LegalMove{ .move = move, .moveType = moveType }, static_cast<int>(moves_.size()) + 1);
        colourToMove_ = oppositeColour(colourToMove_);
        updateLegalMoves();
        if (legalMoves_.empty()) {
            hasEnded_ = true;
            if (board_.isInCheck(colourToMove_)) {
                winner_ = oppositeColour(colourToMove_);
            } else {
                winner_ = std::nullopt;
            }
        }
        // TODO: other drawing conditions
        return true;
    }
}

auto Game::printBoard() const -> void {
    board_.printState();
}

auto Game::getWinner() const -> std::optional<PieceColour> {
    return winner_;
}

auto Game::hasEnded() const -> bool {
    return hasEnded_;
}

auto Game::getColourToMove() const -> PieceColour {
    return colourToMove_;
}

auto Game::updateLegalMoves() -> void {
    legalMoves_ = std::vector<LegalMove>();
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE;  col++) {
            const auto from = Square(row, col);
            const auto piece = board_.pieceAt(from).lock();
            if (piece && piece->isColour(colourToMove_)) {
                for (auto const& legalMove : piece->getLegalMoves(board_, from)) {
                    if (validateLegalMove(legalMove)) {
                        legalMoves_.push_back(legalMove);
                    }
                }
            }
        }
    }
}

auto Game::validateLegalMove(const LegalMove& legalMove) const -> bool {
    auto isValid = false;
    switch(legalMove.moveType) {
        case MoveType::None:
            break;

        case MoveType::Move:
            isValid = true;
            break;

        case MoveType::Capture:
            isValid = true;
            break;

        case MoveType::KingsideCastle:
            isValid = validateCastle(legalMove.move);
            break;

        case MoveType::QueensideCastle:
            isValid = validateCastle(legalMove.move);
            break;

        case MoveType::EnPassant:
            isValid = validateEnPassant(legalMove.move);
            break;
    }
    if (!isValid) {
        return false;
    }

    auto dupBoard = board_;
    dupBoard.executeMove(legalMove);
    if (dupBoard.isInCheck(colourToMove_)) {
        return false;
    }

    return true;
}

auto Game::validateEnPassant(const Move& move) const -> bool {
    return enPassantTarget_ == move.to;
}

auto Game::validateCastle(const Move& move) const -> bool {
    if (board_.isInCheck(colourToMove_)) {
        std::cout << "Cannot castle while in check" << std::endl;
        return false;
    }

    const auto middleRow = move.from.row;
    const auto middleCol = (move.from.col + move.to.col) / 2;
    const auto middleSquare = Square(middleRow, middleCol);
    if (board_.isSquareAttacked(middleSquare, oppositeColour(colourToMove_))) {
        std::cout << "Cannot castle through an attacked square" << std::endl;
        return false;
    }

    return true;
}

auto Game::getMoveType(const Move& move) const -> MoveType {
    for (const auto& legalMove : legalMoves_) {
        if (legalMove.move == move) {
            return legalMove.moveType;
        }
    }
    return MoveType::None;
}
