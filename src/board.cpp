#include <iostream>
#include <optional>

#include "board.h"
#include "helper.h"
#include "move.h"
#include "square.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/pawn.h"

Board::Board() {
    for (auto col = 0; col < 8; col++) {
        for (auto row = 0; row < 8; row++) {
            if (row == 0 || row == 7) {
                // pieces
                auto colour = row == 0 ? PieceColour::White : PieceColour::Black;
                if (col == 0 || col == 7) {
                    // rooks
                    board_[row][col] = std::make_shared<Rook>(colour);
                } else if (col == 1 || col == 6) {
                    // knights
                    board_[row][col] = std::make_shared<Knight>(colour);
                } else if (col == 2 || col == 5) {
                    // bishops
                    board_[row][col] = std::make_shared<Bishop>(colour);
                } else if (col == 3) {
                    // queen
                    board_[row][col] = std::make_shared<Queen>(colour);
                } else if (col == 4) {
                    // king
                    board_[row][col] = std::make_shared<King>(colour);
                }
            } else if (row == 1 || row == 6) {
                auto colour = row == 1 ? PieceColour::White : PieceColour::Black;
                // pawns
                board_[row][col] = std::make_shared<Pawn>(colour);
            }
        }
    }
}

auto Board::updateHasKing() -> void {
    auto whiteHasKing = false;
    auto blackHasKing = false;
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            if (board_[row][col] == nullptr) {
                continue;
            }
            auto symbol = board_[row][col]->getDisplaySymbol();
            if (symbol == 'K') {
                whiteHasKing = true;
            } else if (symbol == 'k') {
                blackHasKing = true;
            }
        }
    }

    whiteHasKing_ = whiteHasKing;
    blackHasKing_ = blackHasKing;
}

// precondition: there is a piece on move.from
auto Board::executeMove(const Move& move, const MoveType& moveType, const int& moveNum) -> void {
    board_[move.to.row][move.to.col] = std::move(board_[move.from.row][move.from.col]);
    board_[move.to.row][move.to.col]->setLastMoved(moveNum);

    switch (moveType) {
        case MoveType::EnPassant:
            board_[move.from.row][move.to.col].reset();

        default:
            return;
    }

    updateHasKing();
}

auto Board::printState() const -> void {
    for (auto row = 7; row >= 0; row--) {
        for (auto col = 0; col < 8; col++) {
            std::cout << (board_[row][col] == nullptr ? '.' : board_[row][col]->getDisplaySymbol()) << " ";
        }
        std::cout << std::endl;
    }
}

auto Board::hasEnded() const -> bool {
    return !(whiteHasKing_ && blackHasKing_);
}

auto Board::getWinner() const -> std::optional<PieceColour> {
    if (whiteHasKing_ && !blackHasKing_) {
        return PieceColour::White;
    } else if (!whiteHasKing_ && blackHasKing_) {
        return PieceColour::Black;
    } else {
        return std::nullopt;
    }
}

auto Board::pieceAt(const Square& square) const -> std::weak_ptr<Piece> {
    return board_[square.row][square.col];
}
