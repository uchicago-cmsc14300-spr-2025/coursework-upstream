#ifndef __COMPUTER_PLAYER_H__
#define __COMPUTER_PLAYER_H__

#include "knightshift.h"

enum choice {CHOICE_NONE, CHOICE_FORT, CHOICE_MOVE};

// return a random move among available
// return NULL if there are none
move *random_move(board *b, color curr);

// return basic evaluation of board per HW7 documentation
int base_heuristic(board *b);

// come up with your own better heuristic
int custom_heuristic(board *b);

// choose a move per minimax analysis
// the three last are out parameters
// `enum choice c` is a tag indicating type of result
// one of f and m should point to decision
// one of f and m should point to NULL
int minimax(int(*heuristic)(board*),
	    board *b, unsigned int depth, color curr,
	    enum choice *c, loc **f, move **m);

#endif
