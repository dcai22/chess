#include "pawn.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Pawn::Pawn(const PieceColour& colour)
: Piece(Constants::PAWN_SYMBOL, Constants::PAWN_SYMBOL, colour, getStartingRow(colour))
, direction_(colour == PieceColour::White ? 1 : -1)
{}

auto Pawn::getStartingRow(const PieceColour& colour) const noexcept -> int {
    return colour == PieceColour::White ? 1 : 6;
}

auto Pawn::getAttackedSquares(const Board& board, const Square& from) const -> std::vector<Square> {
    auto attackedSquares = std::vector<Square>();

    const auto rowStep = direction_;
    const auto colSteps = {1, -1};
    for (const auto& colStep : colSteps) {
        const auto toRow = from.row + rowStep;
        const auto toCol = from.col + colStep;
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (!(toPiece && toPiece->isColour(getColour()))) {
            attackedSquares.push_back(to);
        }
    }
    return attackedSquares;
}

auto Pawn::getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> {
    auto legalMoves = std::vector<LegalMove>();
    const auto rowStep = direction_;

    // move
    const auto maxNumSteps = hasMoved() ? 1 : 2;
    for (auto numSteps = 1; numSteps <= maxNumSteps; numSteps++) {
        const auto toRow = from.row + numSteps * rowStep;
        const auto toCol = from.col;
        if (!Square::isValid(toRow, toCol)) {
            break;
        }

        const auto to = Square(toRow, toCol);
        if (board.pieceAt(to).lock()) {
            break;
        } else {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Move });
        }
    }

    // capture
    const auto colSteps = {-1, 1};
    for (const auto& colStep : colSteps) {
        const auto toRow = from.row + rowStep;
        const auto toCol = from.col + colStep;
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece && !toPiece->isColour(getColour())) {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Capture });
            continue;
        }

        // en-passant
        const auto enPassantRow = from.row;
        const auto enPassantCol = from.col + colStep;
        if (!Square::isValid(enPassantRow, enPassantCol)) {
            continue;
        }

        const auto enPassantSquare = Square(enPassantRow, enPassantCol);
        const auto enPassantPiece = board.pieceAt(enPassantSquare).lock();
        if (enPassantPiece && enPassantPiece->isPawn() && !enPassantPiece->isColour(getColour())) {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::EnPassant });
        }
    }

    return legalMoves;
}
