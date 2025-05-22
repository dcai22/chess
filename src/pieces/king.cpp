#include "king.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

King::King(const PieceColour colour)
: Piece(Constants::KING_VALUE, Constants::KING_SYMBOL, colour)
{}

auto King::getStartingRow() const -> int {
    return getColour() == PieceColour::White ? 0 : 7;
}

auto King::isAttack(const Board& board, const Move& move) const -> bool {
    const auto moveType = deduceMoveType(board, move);
    return moveType == MoveType::Move || moveType == MoveType::Capture;
}

// TODO: castling logic
auto King::deduceMoveType(const Board& board, const Move& move) const -> MoveType {
    const auto fromRow = move.from.row;
    const auto fromCol = move.from.col;

    const auto directions = std::vector<std::vector<int>>({{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}});
    for (const auto& direction : directions) {
        const auto toRow = fromRow + direction[0];
        const auto toCol = fromCol + direction[1];
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (to == move.to) {
            if (toPiece) {
                if (toPiece->getColour() != getColour()) {
                    return MoveType::Capture;
                }
            } else {
                return MoveType::Move;
            }
        }
    }

    // castling
    const auto kingRow = getStartingRow();
    const auto kingCol = 4;
    const auto kingSquare = Square(kingRow, kingCol);
    const auto kingsideRookSquare = Square(kingRow, 7);
    const auto queensideRookSquare = Square(kingRow, 0);
    if (!hasMoved() && move.from == kingSquare) {
        if (move.to == Square(kingRow, kingCol + 2)) {
            const auto kingsideRook = board.pieceAt(kingsideRookSquare).lock();
            if (kingsideRook && kingsideRook->getSymbol() == Constants::ROOK_SYMBOL && kingsideRook->getColour() == getColour() && !kingsideRook->hasMoved()) {
                auto squaresAreEmpty = true;
                for (auto col = kingSquare.col + 1; col < kingsideRookSquare.col; col++) {
                    if (board.pieceAt(Square(kingRow, col)).lock()) {
                        squaresAreEmpty = false;
                        break;
                    }
                }
                if (squaresAreEmpty) {
                    return MoveType::KingsideCastle;
                }
            }
        } else if (move.to == Square(kingRow, kingCol - 2)) {
            const auto queensideRook = board.pieceAt(queensideRookSquare).lock();
            if (queensideRook && queensideRook->getSymbol() == Constants::ROOK_SYMBOL && queensideRook->getColour() == getColour() && !queensideRook->hasMoved()) {
                auto squaresAreEmpty = true;
                for (auto col = kingSquare.col -  1; col > queensideRookSquare.col; col--) {
                    if (board.pieceAt(Square(kingRow, col)).lock()) {
                        squaresAreEmpty = false;
                        break;
                    }
                }
                if (squaresAreEmpty) {
                    return MoveType::QueensideCastle;
                }
            }
        }
    }

    return MoveType::None;
}
