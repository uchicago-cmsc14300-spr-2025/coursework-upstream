#include <criterion/criterion.h>
#include <stdio.h>
#include "hw4.h"

// ======== tests

Test(hw4_color_of, color_of00) {
  cr_assert(color_of(BB)==BLACK);
}

Test(hw4_color_of, color_of01) {
  cr_assert(color_of(WN)==WHITE);
}

Test(hw4_board_empty, board_empty00) {
  chessboard *b = board_empty();
  cr_assert(b->cells[0]==0X00);
}

Test(hw4_board_setup, board_setup00) {
  chessboard *b = board_setup();
  cr_assert(b->cells[0] = (WR<<4)|WN);
}

Test(hw4_board_get, board_get00) {
  chessboard *b = board_empty();
  loc k = {'D',7};
  cr_assert(board_get(b,k)==0);
}

Test(hw4_board_set, board_set00) {
  chessboard *b = board_empty();
  loc a1 = {'A',1};
  board_set(b,a1,BQ);
  cr_assert(b->cells[0]==(BQ<<4));
}

move make_move(char srcFile, char srcRank, char dstFile, char dstRank)
{
  loc s;
  s.file = srcFile;
  s.rank = srcRank;
  loc d;
  d.file = dstFile;
  d.rank = dstRank;
  move m;
  m.src = s;
  m.dst = d;
  return m;
}

Test(hw4_board_do, board_do00) {
  move mv = make_move('A',1,'B',1);
  chessboard *b = board_empty();
  board_set(b,mv.src,BP);
  //fprintf(stderr,"(56)board_do00 cell 0 %X\n",b->cells[0]);
  board_do(b,mv);
  //fprintf(stderr,"(58)board_do00 cell 0 %X\n",b->cells[0]);
  cr_assert(b->cells[0]==BP);
}

Test(hw4_move_knight, move_knight00)
{
  move mv = make_move('A',1,'B',3);
  chessboard *b = board_empty();
  char out;
  b->cells[0] = BN<<4;
  move_knight(b,mv,&out);
  cr_assert(b->cells[0]==0 && b->cells[8]==BN && out==0);
}

Test(hw4_move_rook, move_rook00)
{
  move mv = make_move('A',1,'D',1);
  chessboard *b = board_empty();
  char out;
  b->cells[0] = BR<<4;
  move_rook(b,mv,&out);
  /* fprintf(stderr, */
  /* 	  "(move_rook00) cells[0] 0X%02X cells[1] 0X%02X out %d\n", */
  /* 	  b->cells[0], b->cells[1], out); */
  cr_assert(b->cells[0]==0 && b->cells[1]==BR && out==0);
}

Test(hw4_move_bishop, move_bishop00)
{
  move mv = make_move('A',1,'B',2);
  chessboard *b = board_empty();
  char out;
  b->cells[0] = BB<<4;
  move_bishop(b,mv,&out);
  cr_assert(b->cells[0]==0 && b->cells[4]==BB && out==0);
}

Test(hw4_move_queen, move_queen00)
{
  move mv = make_move('A',1,'B',1);
  chessboard *b = board_empty();
  char out;
  b->cells[0] = BQ<<4;
  move_queen(b,mv,&out);
  cr_assert(b->cells[0]==BQ && out==0);
}

Test(hw4_move_piece, move_piece00)
{
  move mv = make_move('A',1,'A',2);
  chessboard *b = board_empty();
  char out;
  b->cells[0] = BK<<4;
  move_piece(b,mv,&out);
  cr_assert(out==ERR_UNIMPLEMENTED);
}
