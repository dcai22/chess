#include "knight.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Knight::Knight(const PieceColour colour)
: Piece(Constants::KNIGHT_SYMBOL, Constants::KNIGHT_SYMBOL, colour)
{}

auto Knight::canDoMove(const Board& board, const Move& move) const -> bool {
    const auto fromRow = move.from.row;
    const auto fromCol = move.from.col;

    const auto directions = std::vector<std::vector<int>>({{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}});
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
