#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "knightshift.h"
#include "computer-player.h"
#include "knightshell.h"

move *random_move(board *b, color curr)
{
  move_list *ms = available_moves(b,curr);
  if (!ms)
    return NULL;
  move_list *tmp = ms;
  int len = 0;
  for (;tmp;tmp=tmp->next)
    ++len;
  srandom(time(NULL));
  int n = random()%len;
  tmp = ms;
  while (n>0) {
    --n;
    tmp=tmp->next;
  }
  move *result = move_dup(tmp->m);
  mfree(ms);
  return result;
}

int custom_heuristic(board *b)
{
  fprintf(stderr,"TODO: custom_heuristic\n");
  exit(1);
}

int base_heuristic(board *b)
{
  fprintf(stderr,"TODO: base_heuristic\n");
  exit(1);
}

int minimax(int(*heuristic)(board*),
	    board *b, unsigned int depth, color curr,
	    enum choice *c, loc **f, move **m)
{
  fprintf(stderr,"TODO: minimax\n");
  exit(1);
}
