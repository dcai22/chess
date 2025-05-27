# Chess
A command-line interface (CLI) implementation of Chess in modern C++.
This project focuses on rule correctness and clean object-oriented design.
Adhering to SOLID principles grants extensibility for creating an AI engine and a graphical user interface.

## Features
- Turn-based player input in algebraic notation (e.g, `e2 e4`)
- Full move validation
  - Standard move and capture rules for all pieces: Pawn, Rook, Knight, Bishop, Queen, King
  - Special pawn moves: double pawn push and en-passant
  - Kingside and Queenside castling
- Game end detection
  - Checkmate
  - Stalemate
  - Fifty move rule
  - Threefold repetition
  - Insufficient material
- Internal board representation with smart pointers for safe memory management

## Future Plans
- Basic AI opponent
- GUI frontend
- Time control and multiplayer features

## Build & Run
### Requirements
- C++20 or higher
- CMake 3.16 or higher
- A C++ compiler

### Build Instructions
Clone the repository:
```bash
# with HTTPS
git clone https://github.com/dcai22/chess.git

# or with SSH
git clone git@github.com:dcai22/chess.git
```
Build and run the app:
```bash
cd chess
mkdir build
cd build
cmake ..
make
./chess
```

## How to Play
Once the game starts, players will be prompted to enter moves in coordinate notation:
```txt
e2 e4
e7 e5
g1 f3
...
```
If an illegal move is entered, the player will be notified and prompted to enter a legal move.
The game ends when a checkmate or stalemate is detected, or another draw condition is fulfilled.
