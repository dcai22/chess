#include <iostream>
#include <optional>
#include <set>

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
    for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
        for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
            if (row == 0 || row == Constants::BOARD_SIZE - 1) {
                // pieces
                auto colour = row == 0 ? PieceColour::White : PieceColour::Black;
                if (col == 0 || col == Constants::BOARD_SIZE - 1) {
                    // rooks
                    board_[row][col] = std::make_shared<Rook>(colour);
                } else if (col == 1 || col == Constants::BOARD_SIZE - 2) {
                    // knights
                    board_[row][col] = std::make_shared<Knight>(colour);
                } else if (col == 2 || col == Constants::BOARD_SIZE - 3) {
                    // bishops
                    board_[row][col] = std::make_shared<Bishop>(colour);
                } else if (col == 3) {
                    // queen
                    board_[row][col] = std::make_shared<Queen>(colour);
                } else if (col == 4) {
                    // king
                    board_[row][col] = std::make_shared<King>(colour);
                }
            } else if (row == 1 || row == Constants::BOARD_SIZE - 2) {
                auto colour = row == 1 ? PieceColour::White : PieceColour::Black;
                // pawns
                board_[row][col] = std::make_shared<Pawn>(colour);
            }
        }
    }
}

auto Board::getKingSquare(const PieceColour& colour) const noexcept -> std::optional<Square> {
    const auto targetSymbol = King(colour).getDisplaySymbol();
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            const auto& piece = board_[row][col];
            if (piece && piece->getDisplaySymbol() == targetSymbol) {
                return Square(row, col);
            }
        }
    }
    return std::nullopt;
}

auto Board::executeMove(const LegalMove& legalMove) noexcept -> void {
    const auto from = legalMove.move.from;
    const auto to = legalMove.move.to;
    board_[to.row][to.col] = std::move(board_[from.row][from.col]);
    board_[from.row][from.col].reset();

    switch (legalMove.moveType) {
        case MoveType::KingsideCastle: {
            const auto middleRow = from.row;
            const auto middleCol = (from.col + to.col) / 2;
            const auto rookRow = from.row;
            const auto rookCol = 7;
            board_[middleRow][middleCol] = std::move(board_[rookRow][rookCol]);
            break;
        }

        case MoveType::QueensideCastle: {
            const auto middleRow = from.row;
            const auto middleCol = (from.col + to.col) / 2;
            const auto rookRow = from.row;
            const auto rookCol = 0;
            board_[middleRow][middleCol] = std::move(board_[rookRow][rookCol]);
            break;
        }

        case MoveType::EnPassant:
            board_[from.row][to.col].reset();
            break;

        default:
            break;
    }
}

// precondition: there is a piece on move.from, and moveType != MoveType::None
auto Board::processMove(const LegalMove& legalMove, const int moveNum) -> void {
    executeMove(legalMove);

    const auto to = legalMove.move.to;
    auto& piece = board_[to.row][to.col];
    if (piece == nullptr) {
        throw std::logic_error("Piece did not move correctly");
    }

    if (piece->isPawn() && (to.row == 0 || to.row == Constants::BOARD_SIZE - 1)) {
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
    if (legalMove.moveType == MoveType::KingsideCastle || legalMove.moveType == MoveType::QueensideCastle) {
        const auto from = legalMove.move.from;
        const auto middleRow = from.row;
        const auto middleCol = (from.col + to.col) / 2;
        if (!Square::isValid(middleRow, middleCol)) {
            throw std::logic_error("Internal error: square doesn't exist on board");
        }
        board_[middleRow][middleCol]->setLastMoved(moveNum);
    }
}

auto Board::printState() const noexcept -> void {
    for (auto row = Constants::BOARD_SIZE - 1; row >= 0; row--) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            const auto& piece = board_[row][col];
            std::cout << (piece ? piece->getDisplaySymbol() : '.') << " ";
        }
        std::cout << std::endl;
    }
}

auto Board::pieceAt(const Square& square) const -> std::weak_ptr<Piece> {
    return board_[square.row][square.col];
}

auto Board::isSquareAttacked(const Square& square, const PieceColour& byColour) const -> bool {
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            const auto& piece = board_[row][col];
            if (!(piece && piece->isColour(byColour))) {
                continue;
            }
            const auto from = Square(row, col);
            const auto move = Move(from, square);
            if (piece->isAttack(*this, move)) {
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

auto Board::isBigPawnPush(const Move& move) const -> bool {
    const auto& piece = board_[move.from.row][move.from.col];
    return piece && piece->isPawn() && abs(move.to.row - move.from.row) == 2;
}

auto Board::getPositionString() const -> std::string {
    auto state = std::string();
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            const auto& piece = board_[row][col];
            state += piece ? piece->getDisplaySymbol() : '.';
        }
    }
    return state;
}

auto Board::hasInsufficientMaterial() const -> bool {
    auto allPieces = std::multiset<char>();
    for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
        for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
            const auto& piece = board_[row][col];
            if (piece && !piece->isKing()) {
                allPieces.insert(piece->getDisplaySymbol());
            }
        }
    }

    // king vs king
    if (allPieces == std::multiset<char>()) {
        // K vs K
        return true;
    } else if (allPieces == std::multiset<char>({'B'}) || allPieces == std::multiset<char>({'b'})) {
        // K vs K+B
        return true;
    } else if (allPieces == std::multiset<char>({'N'}) || allPieces == std::multiset<char>({'n'})) {
        // K vs K+N
        return true;
    } else if (allPieces == std::multiset<char>({'N', 'N'}) || allPieces == std::multiset<char>({'n', 'n'})) {
        // K vs K+N+N (technically possible but requires cooperation)
        return true;
    } else if (allPieces == std::multiset<char>({'B', 'b'})) {
        // K+B vs K+B is a draw if they are same colour
        auto numWhiteBishops = 0;
        for (auto row = 0; row < Constants::BOARD_SIZE; row++) {
            for (auto col = 0; col < Constants::BOARD_SIZE; col++) {
                const auto& piece = board_[row][col];
                if (piece && piece->isBishop() && (row + col) % 2) {
                    numWhiteBishops++;
                }
            }
        }
        if (numWhiteBishops != 1) {
            return true;
        }
    }
    // other draws are possible, but they are too rare and unrealistic to consider
    // e.g. K+B+B vs K, or K+B+B+B vs K, if all bishops are the same colour

    return false;
}
