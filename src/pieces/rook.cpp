#include "rook.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Rook::Rook(const PieceColour colour)
: Piece(Constants::ROOK_SYMBOL, Constants::ROOK_SYMBOL, colour)
{}

auto Rook::canDoMove(const Board& board, const Move& move) const -> bool {
    const auto fromRow = move.from.row;
    const auto fromCol = move.from.col;

    const auto directions = std::vector<std::vector<int>>({{0, 1}, {0, -1}, {1, 0}, {-1, 0}});
    for (const auto& direction : directions) {
        auto toRow = fromRow;
        auto toCol = fromCol;
        while (true) {
            toRow += direction[0];
            toCol += direction[1];
            if (!Square::isValid(toRow, toCol)) {
                break;
            }

            const auto to = Square(toRow, toCol);
            const auto toPiece = board.pieceAt(to).lock();
            if (toPiece && toPiece->getColour() == getColour()) {
                // reached piece of same colour
                break;
            } else if (to == move.to) {
                // reached desired square
                return true;
            } else if (toPiece && toPiece->getColour() != getColour()) {
                // reached a piece, wrong square
                break;
            }
        }
    }

    return false;
}
