#include "knight.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Knight::Knight(const PieceColour colour)
: Piece(Constants::KNIGHT_SYMBOL, Constants::KNIGHT_SYMBOL, colour)
{}

// auto Knight::deduceMoveType(const Board& board, const Move& move) const -> MoveType {
//     const auto fromRow = move.from.row;
//     const auto fromCol = move.from.col;

//     const auto directions = std::vector<std::vector<int>>({{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}});
//     for (const auto& direction : directions) {
//         const auto toRow = fromRow + direction[0];
//         const auto toCol = fromCol + direction[1];
//         if (!Square::isValid(toRow, toCol)) {
//             continue;
//         }

//         const auto to = Square(toRow, toCol);
//         const auto toPiece = board.pieceAt(to).lock();
//         if (to == move.to) {
//             if (toPiece) {
//                 if (toPiece->getColour() != getColour()) {
//                     return MoveType::Capture;
//                 }
//             } else {
//                 return MoveType::Move;
//             }
//         }
//     }

//     return MoveType::None;
// }

auto Knight::getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> {
    auto legalMoves = std::vector<LegalMove>();
    const auto directions = std::vector<std::vector<int>>({{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}});
    for (const auto& direction : directions) {
        const auto toRow = from.row + direction[0];
        const auto toCol = from.col + direction[1];
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece) {
            if (toPiece->getColour() != getColour()) {
                const auto move = Move(from, to);
                legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Capture });
            }
        } else {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Move });
        }
    }

    return legalMoves;
}
