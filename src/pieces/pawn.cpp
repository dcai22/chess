#include "pawn.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Pawn::Pawn(const PieceColour colour)
: Piece(Constants::PAWN_SYMBOL, Constants::PAWN_SYMBOL, colour)
{}

// TODO: implement en-passant and promotion
auto Pawn::canDoMove(const Board& board, const Move& move) const -> bool {
    auto fromRow = move.from.row;
    auto fromCol = move.from.col;

    const auto rowStep = getColour() == PieceColour::White ? 1 : -1;

    // move
    const auto maxNumSteps = hasMoved() ? 1 : 2;
    for (auto numSteps = 1; numSteps <= maxNumSteps; numSteps++) {
        const auto toRow = fromRow + numSteps * rowStep;
        const auto toCol = fromCol;
        if (!Square::isValid(toRow, toCol)) {
            break;
        }

        const auto to = Square(toRow, toCol);
        if (board.pieceAt(to).lock()) {
            break;
        } else if (to == move.to) {
            return true;
        }
    }

    // capture
    const auto colSteps = {-1, 1};
    for (const auto& colStep : colSteps) {
        const auto toRow = fromRow + rowStep;
        const auto toCol = fromCol + colStep;

        if (!Square::isValid(toRow, toCol)) {
            break;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece && toPiece->getColour() != getColour() && to == move.to) {
            return true;
        }
    }

    return false;
}
