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

auto Board::getKingSquare(const PieceColour& colour) const -> std::optional<Square> {
    const auto targetSymbol = King(colour).getDisplaySymbol();
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            if (board_[row][col] && board_[row][col]->getDisplaySymbol() == targetSymbol) {
                return Square(row, col);
            }
        }
    }
    return std::nullopt;
}

auto Board::executeMove(const Move& move, const MoveType& moveType) -> void {
    board_[move.to.row][move.to.col] = std::move(board_[move.from.row][move.from.col]);
    board_[move.from.row][move.from.col].reset();

    switch (moveType) {
        case MoveType::KingsideCastle: {
            const auto middleRow = move.from.row;
            const auto middleCol = (move.from.col + move.to.col) / 2;
            const auto rookRow = move.from.row;
            const auto rookCol = 7;
            board_[middleRow][middleCol] = std::move(board_[rookRow][rookCol]);
            break;
        }

        case MoveType::QueensideCastle: {
            const auto middleRow = move.from.row;
            const auto middleCol = (move.from.col + move.to.col) / 2;
            const auto rookRow = move.from.row;
            const auto rookCol = 0;
            board_[middleRow][middleCol] = std::move(board_[rookRow][rookCol]);
            break;
        }

        case MoveType::EnPassant: {
            board_[move.from.row][move.to.col].reset();
            break;
        }

        default:
            return;
    }
}

// precondition: there is a piece on move.from, and moveType != MoveType::None
auto Board::processMove(const Move& move, const MoveType& moveType, const int moveNum) -> void {
    executeMove(move, moveType);

    auto& piece = board_[move.to.row][move.to.col];
    if (piece == nullptr) {
        throw std::logic_error("Piece did not move correctly");
    }

    if (piece->getSymbol() == Constants::PAWN_SYMBOL &&
    (move.to.row == 0 || move.to.row == Constants::BOARD_SIZE - 1)) {
        // promotion
        printState();
        std::cout << "What piece would you like to promote your pawn to?" << std::endl;
        std::cout << Constants::QUEEN_SYMBOL << ": Queen" << std::endl;
        std::cout << Constants::ROOK_SYMBOL << ": Rook" << std::endl;
        std::cout << Constants::BISHOP_SYMBOL << ": Bishop" << std::endl;
        std::cout << Constants::KNIGHT_SYMBOL << ": Knight" << std::endl;
        std::cout << "Enter symbol: ";

        while (true) {
            auto input = std::string();
            std::getline(std::cin >> std::ws, input);
            const auto tokens = splitByWhitespace(input);
            if (tokens.size() != 1 || tokens[0].size() != 1) {
                continue;
            }

            const auto pieceColour = piece->getColour();
            const auto symbol = tokens[0][0];
            auto success = true;
            switch (symbol) {
                case 'N':
                    piece = std::make_shared<Knight>(pieceColour);
                    break;

                case 'B':
                    piece = std::make_shared<Bishop>(pieceColour);
                    break;

                case 'R':
                    piece = std::make_shared<Rook>(pieceColour);
                    break;

                case 'Q':
                    piece = std::make_shared<Queen>(pieceColour);
                    break;

                default:
                    success = false;
                    break;
            }

            if (success) {
                break;
            }
        }
    }

    piece->setLastMoved(moveNum);
    // castled
    if (moveType == MoveType::KingsideCastle || moveType == MoveType::QueensideCastle) {
        const auto middleRow = move.from.row;
        const auto middleCol = (move.from.col + move.to.col) / 2;
        board_[middleRow][middleCol]->setLastMoved(moveNum);
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

auto Board::isSquareAttacked(const Square& square, const PieceColour& byColour) const -> bool {
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            if (board_[row][col] == nullptr || board_[row][col]->getColour() != byColour) {
                continue;
            }
            const auto from = Square(row, col);
            const auto move = Move(from, square);
            if (board_[row][col]->isAttack(*this, move)) {
                return true;
            }
        }
    }
    return false;
}

auto Board::isInCheck(const PieceColour& playerColour) const -> bool {
    const auto kingSquareOpt = getKingSquare(playerColour);
    if (kingSquareOpt.has_value()) {
        return isSquareAttacked(kingSquareOpt.value(), oppositeColour(playerColour));
    } else {
        return false;
    }
}
