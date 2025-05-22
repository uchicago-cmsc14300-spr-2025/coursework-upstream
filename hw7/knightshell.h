#ifndef __KNIGHTSHELL_H__
#define __KNIGHTSHELL_H__

#include "knightshift.h"

typedef enum {
  MOVE,
  FORTIFY,
  HELP,
  QUIT,
  UNKNOWN
} turn;

typedef struct {
  turn category;
  loc src;
  loc dst;
} command;

// build a board from an array of characters, for convenience (and testing)
board *quick_board(char *ranks[]);

// parse a command from a string like "M C1 C2"
command parse(char *s);

// display the board
void board_show(board *b);

// display a command
void command_show(command cmd);

// show help information in the shell for players
void help_show();

// show errors
void error_show(int outcome);

#endif
