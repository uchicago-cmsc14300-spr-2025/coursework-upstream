#ifndef __HW3_H__
#define __HW3_H__

#include <stdlib.h>
#include <stdio.h>

// Use the constant names throughout the code; that is, write WP and not 1.

// chess piece constants
// NOTE: the value 0 is not used; 0 means "no piece"

// The use of "static const" allows these to be defined in the header
// without causing compile errors.

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

// error constants

static const int ERR_NO_PIECE = 64;
static const int ERR_PIECE_TYPE = 65;
static const int ERR_BAD_MOVE = 66;
static const int ERR_FRIENDLY = 67;
static const int ERR_BAD_LOCATION = 68;

// -------------------------------------------------

// a chess board location is specified by
// a rank, a character from 'A' through 'H' inclusive, and
// a file, a number from 1 to 8 inclusive

// in the comments below, "raise error" means
// print a message to stderr and exit(1)

// return a string corresponding to the piece
// return the string "no piece" for p==0
// GIGO for non-piece arguments (except 0)
// this function is for *you* and will not be scored by us
char *piece_str(piece p);

// return a pointer to a new piece array of length 64
// it must be located on the heap
// all squares empty
piece *board_empty();

// return a pointer to a new piece array of length 64
// it must be located on the heap
// it should be the initial setup for a game of chess
piece *board_setup();

// get the piece at the given position
// raise error if rank, file is not on the board
piece board_get(piece *board, char rank, char file);

// put the piece at the given position
// NOTE: if the last argument is 0, clear the square
// raise error if rank, file is not on the board
// GIGO if the piece p is not a piece const or 0
void board_set(piece *board, char rank, char file, piece p);
	     
// take the piece at src and put it at dst
// if there is no piece at src, do nothing (but no error)
// raise error if any rank or file is not on the board
void board_do(piece *board,
	      char src_rank, char src_file,
	      char dst_rank, char dst_file);

// move the knight at src_rank, src_file to dst_rank, dst_file
// the code should not crash or exit, even when something is wrong
// if there is no piece at dst, move knight and set outcome to 0
// if there is an opponent's piece at dst, move knight and set outcome to captured piece
// there are various things that can go wrong:
// if src and/or dst is off the board, set outcome to ERR_BAD_LOCATION
// if there is no piece at src, set outcome to ERR_NO_PIECE
// if there is a non-knight at src, set outcome to ERR_PIECE_TYPE
// if the move is not a knight's move, geometrically, set outcome to ERR_BAD_MOVE
// if dst is occupied by a friendly piece, set outcome to ERR_FRIENDLY
void move_knight(piece *board,
		 char src_rank, char src_file,
		 char dst_rank, char dst_file,
		 char *outcome);

#endif
