#include "king.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

King::King(const PieceColour colour)
: Piece(Constants::KING_VALUE, Constants::KING_SYMBOL, colour)
{}

// TODO: castling logic
auto King::canDoMove(const Board& board, const Move& move) const -> bool {
    const auto fromRow = move.from.row;
    const auto fromCol = move.from.col;

    const auto directions = std::vector<std::vector<int>>({{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, 1}});
    for (const auto& direction : directions) {
        const auto toRow = fromRow + direction[0];
        const auto toCol = fromCol + direction[1];
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece && toPiece->getColour() == getColour()) {
            // piece has same colour
            continue;
        } else if (to == move.to) {
            // reached desired square
            return true;
        }
    }

    return false;
}
