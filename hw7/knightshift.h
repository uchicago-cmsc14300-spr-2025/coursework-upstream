#ifndef __KNIGHTSHIFT_H__
#define __KNIGHTSHIFT_H__

// ======== constants

// these ERR constants are carried over from HW4
// not all of them are used in this spec
#define ERR_NO_PIECE 64
#define ERR_PIECE_TYPE 65
#define ERR_BAD_MOVE 66
#define ERR_FRIENDLY 67
#define ERR_BAD_LOCATION 68
#define ERR_UNIMPLEMENTED 69

// these are not used in HW6
#define VICTORY_WHITE_TWO_FORTRESSES 32
#define VICTORY_BLACK_TWO_FORTRESSES 33
#define VICTORY_WHITE_THREE_CAPTURES 34
#define VICTORY_BLACK_THREE_CAPTURES 35

// these unicode strings may be used for display
#define UNICODE_KING_WHITE    "♔" 
#define UNICODE_ROOK_WHITE    "♖"
#define UNICODE_KNIGHT_WHITE  "♘"
#define UNICODE_KING_BLACK    "♚" 
#define UNICODE_ROOK_BLACK    "♜"
#define UNICODE_KNIGHT_BLACK  "♞"

// ======== data definitions

typedef enum {
  BLACK,
  WHITE
} color;

typedef enum {
  KNIGHT, 
  ROYAL_GUARD,
  FORTRESS
} piece_type;

typedef struct piece {
  color color;
  piece_type type;
} piece;

typedef struct board {
  // array of piece *pointers*, NULL means no piece
  piece *squares[40];
} board;

typedef struct loc {
  char file;
  char rank;
} loc;

typedef struct move {
  loc src;
  loc dst;
} move;

typedef struct piece_list {
  piece p;
  struct piece_list *next;
} piece_list;

typedef struct loc_list {
  loc k;
  struct loc_list *next;
} loc_list;

typedef struct move_list {
  move m;
  struct move_list *next;
} move_list;

// ======== operations

// -------- piece operations

piece *piece_new(color color, piece_type type);

piece *piece_dup(piece *p);

char *piece_tos(piece *p);

int piece_eq(piece *p1, piece *p2);

// -------- loc operations

loc loc_new(char file, char rank);

loc *loc_dup(loc k);

char *loc_tos(loc k);

int loc_eq(loc k1, loc k2);

// -------- move operations

move move_new(loc src, loc dst);

move *move_dup(move m);

char *move_tos(move m);

int move_eq(move m1, move m2);

// -------- piece_list operations

piece_list *pcons(piece p, piece_list *pieces);

void pfree(piece_list *pieces);

void pshow(piece_list *pieces);

unsigned int plen(piece_list *pieces);

// -------- loc_list operations

loc_list *lcons(loc k, loc_list *locs);

void lfree(loc_list *locs); 

void lshow(loc_list *locs);

unsigned int llen(loc_list *locs);

// -------- move_list operations

move_list *mcons(move m, move_list *moves);

void mfree(move_list *moves); 

void mshow(move_list *moves);

unsigned int mlen(move_list *moves);

// --------- game operations

// return a freshly-constructed empty board
board *board_empty();

// return a freshly-constructed board, ready to play the game
board *board_setup();

// return the piece at the location, or NULL for an empty square
// GIGO for bad location
piece *piece_at(board *b, loc k);

// put piece (or NULL) at given location on board uncritically
// (no legality check)
void put_piece(board *b, piece *p, loc k);

// return true if space is not empty, false otherwise
// GIGO for bad location
int occupied(board *b, loc k);

// return true if space is empty, false otherwise
// GIGO for bad location
int unoccupied(board *b, loc k);

// curr means "current player's color"
// return the locations of the current player's pieces
loc_list *pieces_of(board *b, color curr);

// return the (as many as) eight locations that are
// a knight's move away from the argument location
// GIGO for bad location
loc_list *adjacent_knight(loc k);

// return the (as many as) eight locations that are
// a guard's move away from the argument location
// GIGO for bad location
loc_list *adjacent_guard(loc k);

// return the (as many as) four locations that are
// orthogonally adjacent to the argument location
// GIGO for bad location
loc_list *adjacent_ortho(loc k);

// return true if there is a *protected knight* at the location
// a knight is protected when orthogonally adjacent to its own guard
// GIGO for bad location
int protected_knight_at(board *b, loc k);

// return true if proposed move is a legal knight's move for curr color
// for a move to be legal, it must either end on an open space
//   or capture an unprotected opponent's knight
// the move must be of the right shape
// an ill-formed move, for any reason, is not an error, it's just not legal
int legal_knight(board *b, move m, color curr);

// return true if proposed move is a legal guard's move for curr color
// for a move to be legal, it must either end on an open space
//   or capture an unprotected opponent's knight
// it also may not end in the opponent's guard's zone of protection
// the move must be of the right shape
// an ill-formed move, for any reason, is not an error, it's just not legal
int legal_guard(board *b, move m, color curr);

// return a list of all legal moves for the current player
// order does not matter
move_list *available_moves(board *b, color curr);

// return a list of all legal fortifications for the current player
// order does not matter
loc_list *available_fortifications(board *b, color curr);

// apply the given move if possible
// set *outcome to 0 for successful move
// return pointer to captured piece, or NULL for no capture
// if m.src is empty, ERR_NO_PIECE
// if either m.src or m.dst is off the board, ERR_BAD_MOVE
// if m.src has the wrong color piece (not curr), ERR_BAD_MOVE
// if the move is not legal for any other reason, ERR_BAD_MOVE
piece *apply_move(board *b, move m, color curr, int *outcome);

// fortify the given location if possible
// set *outcome to 0 for successful fortification
// if k is off the board, ERR_BAD_LOCATION
// if k is not in the right rank for curr, ERR_BAD_LOCATION
// if there is no piece at k, ERR_NO_PIECE
// if k does not contain a knight, ERR_PIECE_TYPE
// if k has the wrong color piece (not curr), ERR_BAD_MOVE
void fortify(board *b, loc k, color curr, int *outcome);

// return 0 if game is not over
// otherwise return one of the VICTORY constants (see above)
int game_over(board *b);
  
// draw the board
void show_board(board *b);

// return a new board that is the result of fortifying
// GIGO in case of illegitimate fortification
// useful for minimax
board *do_fortify_new(board *b, loc k, color curr);

// return a new board that is the result of applying move
// GIGO in case of bad move
// useful for minimax
board *do_move_new(board *b, move m);

// free board and all pieces pointed to
void board_free(board *b);

#endif
