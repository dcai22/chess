#pragma once

enum class PieceColour {
    White,
    Black,
};

enum class MoveType {
    None,
    Move,
    Capture,
    KingsideCastle,
    QueensideCastle,
    EnPassant,
};
