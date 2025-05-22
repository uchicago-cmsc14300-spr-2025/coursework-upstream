#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "knightshift.h"
#include "computer-player.h"

// ======== helpers for tests

// the prefix GP1 stands for "graders' phase1"
// and makes it unlikely for our function names
// to collide with yours

// this is a stub heuristic function for tests
int GP1constant_1000(board *b)
{
  return 1000;
}

// ======== tests

// note: memory is not freed with 100% conscientiousness

Test(hw7_game_over, game_over00) {
  board *b = board_setup();
  cr_assert(!game_over(b));
  board_free(b);
}

Test(hw7_base_heuristic, base_heuristic00) {
  board *b = board_setup();
  cr_assert(base_heuristic(b)==0);
  board_free(b);
}

Test(hw7_base_heuristic, base_heuristic01) {
  board *b = board_setup();
  // remove one white knight
  b->squares[0]=NULL;
  cr_assert(base_heuristic(b)==-3);
  board_free(b);
}

Test(hw7_custom_heuristic, custom_heuristic00) {
  board *b = board_setup();
  // this is just to make sure it compiles and runs
  int h = custom_heuristic(b);
  cr_assert(h<0 || h==0 || h>0); // unfailiable test
  board_free(b);
}

Test(hw7_minimax, minimax00) {
  board *b = board_setup();
  enum choice c;
  loc *f  = NULL;
  move *m = NULL;
  int score = minimax(&GP1constant_1000,b,0,WHITE,&c,&f,&m);
  cr_assert(score==1000);
  board_free(b);
}

Test(hw7_minimax, minimax01) {
  board *b = board_setup();
  enum choice c;
  loc *f  = NULL;
  move *m = NULL;
  int score = minimax(&GP1constant_1000,b,1,WHITE,&c,&f,&m);
  cr_assert(score==1000);
  board_free(b);
}
