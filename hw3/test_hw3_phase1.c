#include <criterion/criterion.h>
#include <stdio.h>
#include "hw3.h"

// ======== tests

Test(hw3_board_empty, board_empty00)
{
  piece *board = board_empty();
  for (int i=0; i<64; ++i)
    cr_assert(board[i]==0);
  free(board);
}

Test(hw3_board_setup, board_setup00)
{
  piece *board = board_setup();
  cr_assert(board[0]==WR);
  free(board);
}

Test(hw3_board_get, board_get00)
{
  piece *board = board_empty();
  cr_assert(board_get(board,'C',4)==0);
  free(board);
}

Test(hw3_board_set, board_set00)
{
  piece *board = board_empty();
  board_set(board,'D',5,BN);
  cr_assert(board_get(board,'D',5)==BN);
  free(board);
}

Test(hw3_board_do, board_do00)
{
  piece *board = board_setup();
  board_do(board,'A',1,'A',3);
  cr_assert(board_get(board,'A',1)==0 && board_get(board,'A',3)==WR);
  free(board);
}

Test(hw3_move_knight, move_knight00)
{
  piece *board = board_empty();
  char o;
  move_knight(board, 'A', 1, 'C', 2, &o);
  cr_assert(o==ERR_NO_PIECE);
  free(board);
}


