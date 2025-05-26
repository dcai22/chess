#include "king.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

King::King(const PieceColour& colour)
: Piece(Constants::KING_VALUE, Constants::KING_SYMBOL, colour, getStartingRow(colour))
{}

auto King::getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> {
    auto legalMoves = std::vector<LegalMove>();
    for (const auto& direction : directions_) {
        const auto toRow = from.row + direction[0];
        const auto toCol = from.col + direction[1];
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece) {
            if (!toPiece->isColour(getColour())) {
                const auto move = Move(from, to);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Capture });
            }
        } else {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Move });
        }
    }

    // castling
    const auto kingRow = getStartingRow();
    const auto kingCol = 4;
    const auto kingsideRookCol = 7;
    const auto queensideRookCol = 0;
    const auto kingSquare = Square(kingRow, kingCol);
    const auto kingsideRookSquare = Square(kingRow, kingsideRookCol);
    const auto queensideRookSquare = Square(kingRow, queensideRookCol);
    if (!hasMoved() && from == kingSquare) {
        // kingside
        const auto kingsideTo = Square(kingRow, kingCol + 2);
        const auto kingsideRook = board.pieceAt(kingsideRookSquare).lock();
        if (kingsideRook && kingsideRook->isRook() && kingsideRook->isColour(getColour()) && !kingsideRook->hasMoved()) {
            auto squaresAreEmpty = true;
            for (auto col = kingSquare.col + 1; col < kingsideRookSquare.col; col++) {
                if (board.pieceAt(Square(kingRow, col)).lock()) {
                    squaresAreEmpty = false;
                    break;
                }
            }
            if (squaresAreEmpty) {
                const auto move = Move(from, kingsideTo);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::KingsideCastle });
            }
        }

        // queenside
        const auto queensideTo = Square(kingRow, kingCol - 2);
        const auto queensideRook = board.pieceAt(queensideRookSquare).lock();
        if (queensideRook && queensideRook->isRook() && queensideRook->isColour(getColour()) && !queensideRook->hasMoved()) {
            auto squaresAreEmpty = true;
            for (auto col = kingSquare.col -  1; col > queensideRookSquare.col; col--) {
                if (board.pieceAt(Square(kingRow, col)).lock()) {
                    squaresAreEmpty = false;
                    break;
                }
            }
            if (squaresAreEmpty) {
                const auto move = Move(from, queensideTo);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::QueensideCastle });
            }
        }
    }

    return legalMoves;
}
