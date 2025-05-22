#include "pawn.h"
#include "../constants.h"
#include "../board.h"
#include "../move.h"

Pawn::Pawn(const PieceColour colour)
: Piece(Constants::PAWN_SYMBOL, Constants::PAWN_SYMBOL, colour)
{}

// returns 1 if pawn goes up the board, -1 if pawn goes down the board
auto Pawn::getDirection() const -> int {
    return getColour() == PieceColour::White ? 1 : -1;
}

auto Pawn::getAttackedSquares(const Board& board, const Square& from) const -> std::vector<Square> {
    auto attackedSquares = std::vector<Square>();

    const auto rowStep = getDirection();
    const auto colSteps = {1, -1};
    for (const auto& colStep : colSteps) {
        const auto toRow = from.row + rowStep;
        const auto toCol = from.col + colStep;
        if (!Square::isValid(toRow, toCol)) {
            continue;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (!(toPiece && toPiece->getColour() == getColour())) {
            attackedSquares.push_back(to);
        }
    }
    return attackedSquares;
}

// auto Pawn::deduceMoveType(const Board& board, const Move& move) const -> MoveType {
//     const auto fromRow = move.from.row;
//     const auto fromCol = move.from.col;

//     const auto rowStep = getDirection();

//     // move
//     const auto maxNumSteps = hasMoved() ? 1 : 2;
//     for (auto numSteps = 1; numSteps <= maxNumSteps; numSteps++) {
//         const auto toRow = fromRow + numSteps * rowStep;
//         const auto toCol = fromCol;
//         if (!Square::isValid(toRow, toCol)) {
//             break;
//         }

//         const auto to = Square(toRow, toCol);
//         if (board.pieceAt(to).lock()) {
//             break;
//         } else if (to == move.to) {
//             return MoveType::Move;
//         }
//     }

//     // capture
//     const auto colSteps = {-1, 1};
//     for (const auto& colStep : colSteps) {
//         const auto toRow = fromRow + rowStep;
//         const auto toCol = fromCol + colStep;
//         if (Square::isValid(toRow, toCol)) {
//             const auto to = Square(toRow, toCol);
//             const auto toPiece = board.pieceAt(to).lock();
//             if (toPiece && toPiece->getColour() != getColour() && to == move.to) {
//                 return MoveType::Capture;
//             }

//             // en-passant
//             const auto enPassantRow = fromRow;
//             const auto enPassantCol = fromCol + colStep;
//             if (Square::isValid(enPassantRow, enPassantCol)) {
//                 const auto enPassantSquare = Square(enPassantRow, enPassantCol);
//                 const auto enPassantPiece = board.pieceAt(enPassantSquare).lock();
//                 if (enPassantPiece && enPassantPiece->getSymbol() == Constants::PAWN_SYMBOL && enPassantPiece->getColour() != getColour() && to == move.to) {
//                     return MoveType::EnPassant;
//                 }
//             }
//         }
//     }

//     return MoveType::None;
// }

auto Pawn::getLegalMoves(const Board& board, const Square& from) const -> std::vector<LegalMove> {
    auto legalMoves = std::vector<LegalMove>();
    const auto rowStep = getDirection();

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
            break;
        }

        const auto to = Square(toRow, toCol);
        const auto toPiece = board.pieceAt(to).lock();
        if (toPiece && toPiece->getColour() != getColour()) {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::Capture });
            continue;
        }

        // en-passant
        const auto enPassantRow = from.row;
        const auto enPassantCol = from.col + colStep;
        if (!Square::isValid(enPassantRow, enPassantCol)) {
            break;
        }

        const auto enPassantSquare = Square(enPassantRow, enPassantCol);
        const auto enPassantPiece = board.pieceAt(enPassantSquare).lock();
        if (enPassantPiece && enPassantPiece->getSymbol() == Constants::PAWN_SYMBOL && enPassantPiece->getColour() != getColour()) {
            const auto move = Move(from, to);
            legalMoves.push_back(LegalMove{ .move = move, .moveType = MoveType::EnPassant });
        }
    }

    return legalMoves;
}
