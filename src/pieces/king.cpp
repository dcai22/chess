#include "king.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

King::King(const PieceColour colour)
: Piece(Constants::KING_VALUE, Constants::KING_SYMBOL, colour)
{}

// TODO: castling logic
auto King::deduceMoveType(const Board& board, const Move& move) const -> MoveType {
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

    return MoveType::None;
}
