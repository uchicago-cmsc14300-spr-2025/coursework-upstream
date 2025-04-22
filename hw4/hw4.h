#ifndef __HW4_H__
#define __HW4_H__

enum chess_color {
  WHITE = 1,
  BLACK = 2
};

typedef enum chess_color color;

static const int WP = 1;  // white pawn
static const int WN = 2;  // white knight
static const int WB = 3;  // white bishop
static const int WR = 4;  // white rook
static const int WQ = 5;  // white queen
static const int WK = 6;  // white king

static const int BP = 9;  // black pawn
static const int BN = 10; // etc. (as above)
static const int BB = 11;
static const int BR = 12;
static const int BQ = 13;
static const int BK = 14;

typedef int piece;

struct packed_chessboard {
  unsigned char cells[32]; // two squares per cell
};

typedef struct packed_chessboard chessboard;

struct location {
  char file; // 'A' through 'H'
  char rank; //   1 through 8
};

typedef struct location loc;

struct chess_move {
  loc src;
  loc dst;
};

typedef struct chess_move move;

// error constants
static const int ERR_NO_PIECE      = 64;
static const int ERR_PIECE_TYPE    = 65;
static const int ERR_BAD_MOVE      = 66;
static const int ERR_FRIENDLY      = 67;
static const int ERR_BAD_LOCATION  = 68;
static const int ERR_UNIMPLEMENTED = 69;

// -------------------------------------------------

// a chess board location is specified by
// a file, a character from 'A' through 'H' inclusive, and
// a rank, a number from 1 to 8 inclusive

// in the comments below, "raise error" means
// print a message to stderr and exit(1)

// return a string corresponding to the piece
// return the string "no piece" for p==0
// GIGO for non-piece arguments (except 0)
// this function is *for you* and will not be scored by us
char *piece_str(piece p);

// return either WHITE or BLACK
// return 0 if the piece is not one of the piece constants
// (and thus has no color)
color color_of(piece p);

// return a pointer to a new chessboard struct (on the heap)
// all squares empty
chessboard *board_empty();

// return a pointer to a new chessboard struct (on the heap)
// it should be the initial setup for a game of chess
chessboard *board_setup();

// get the piece at the given position
// raise error if loc is not on the board
piece board_get(chessboard *board, loc k);

// put the piece at the given position
// NOTE: if the last argument (p) is 0, clear the square
// raise error if loc is not on the board
// GIGO if the piece p is not a piece const or 0
void board_set(chessboard *board, loc k, piece p);
	     
// take the piece at src and put it at dst
// if there is no piece at src, do nothing (and no error)
// raise error if either move loc is not on the board
void board_do(chessboard *board, move m);

// move the knight at src to dst
// the code should not crash or exit, even when something is wrong
// if no piece at dst, move knight and set outcome to 0
// if opponent's piece at dst, move knight and set outcome to captured piece
// various things can go wrong (in which case don't move any piece):
// - if src and/or dst is off the board, set outcome to ERR_BAD_LOCATION
// - if there is no piece at src, set outcome to ERR_NO_PIECE
// - if there is a non-knight at src, set outcome to ERR_PIECE_TYPE
// - if move is not a knight's move, geometrically, set outcome to ERR_BAD_MOVE
// - if dst is occupied by a friendly piece, set outcome to ERR_FRIENDLY
// *ignore any consideration of exposing the king to check*
void move_knight(chessboard *board, move m, char *outcome);

// move the rook at src to dst
// the code should not crash or exit, even when something is wrong
// various things can go wrong (in which case don't move any piece):
// - if src and/or dst is off the board, set outcome to ERR_BAD_LOCATION
// - if there is no piece at src, set outcome to ERR_NO_PIECE
// - if there is a non-rook at src, set outcome to ERR_PIECE_TYPE
// - if move is not a rook's move, geometrically, set outcome to ERR_BAD_MOVE
// - if the rook's pathway to dst is blocked, set outcome to ERR_BAD_MOVE
// if path to dst is clear,
// - but dst is occupied by friendly piece, set outcome to ERR_FRIENDLY
// - dst is unoccupied, move rook and set outcome to 0
// - dst is occupied by opponent, move rook and set outcome to captured piece
// *ignore any consideration of exposing the king to check*
void move_rook(chessboard *board, move m, char *outcome);

// move the bishop at src to dst
// the code should not crash or exit, even when something is wrong
// various things can go wrong (in which case don't move any piece):
// - if src and/or dst is off the board, set outcome to ERR_BAD_LOCATION
// - if there is no piece at src, set outcome to ERR_NO_PIECE
// - if there is a non-bishop at src, set outcome to ERR_PIECE_TYPE
// - if move is not a bishop's move, geometrically, set outcome to ERR_BAD_MOVE
// - if the bishop's pathway to dst is blocked, set outcome to ERR_BAD_MOVE
// if path to dst is clear,
// - but dst is occupied by friendly piece, set outcome to ERR_FRIENDLY
// - dst is unoccupied, move bishop and set outcome to 0
// - dst is occupied by opponent, move bishop and set outcome to captured piece
// *ignore any consideration of exposing the king to check*
void move_bishop(chessboard *board, move m, char *outcome);

// move the queen at src to dst
// the code should not crash or exit, even when something is wrong
// various things can go wrong (in which case don't move any piece):
// - if src and/or dst is off the board, set outcome to ERR_BAD_LOCATION
// - if there is no piece at src, set outcome to ERR_NO_PIECE
// - if there is a non-queen at src, set outcome to ERR_PIECE_TYPE
// - if move is not a queen's move, geometrically, set outcome to ERR_BAD_MOVE
// - if the queen's pathway to dst is blocked, set outcome to ERR_BAD_MOVE
// if path to dst is clear,
// - but dst is occupied by friendly piece, set outcome to ERR_FRIENDLY
// - dst is unoccupied, move queen and set outcome to 0
// - dst is occupied by opponent, move queen and set outcome to captured piece
// *ignore any consideration of exposing the king to check*
void move_queen(chessboard *board, move m, char *outcome);

// move the knight, bishop, rook, or queen from src to dst
// if src is unoccupied, set outcome to ERR_NO_PIECE
// if src contains a pawn or king, set outcome to ERR_UNIMPLEMENTED
// otherwise, dispatch the move to one of the piece-specific functions above
// *ignore any consideration of exposing the king to check*
void move_piece(chessboard *board, move m, char *outcome);

#endif
