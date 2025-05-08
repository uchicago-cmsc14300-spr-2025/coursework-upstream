#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw6.h"

// ======== helpers for tests

// the prefix GP1 stands for "graders' phase1"
// and makes it unlikely for our function names
// to collide with yours

int GP1piece_eq(piece *p, piece *q)
{
  return p->color==q->color && p->type==q->type;
}

board *GP1empty()
{
  board *e = malloc(sizeof(board));
  if (!e) {
    fprintf(stderr,"(GP1empty) malloc failed\n");
    exit(1);
  }
  for (int i=0; i<40; ++i)
    e->squares[i] = NULL;
  return e;
}

void GP1board_free(board *b)
{
  for (int i=0; i<40; ++i)
    if (b->squares[i])
      free(b->squares[i]);
  free(b);
}

int GP1locs_len(loc_list *locs)
{
  int n = 0;
  for (;locs;locs=locs->next)
    ++n;
  return n;
}

void GP1locs_free(loc_list *locs)
{
  if (locs) {
    GP1locs_free(locs->next);
    free(locs);
  }
}

// ======== tests

Test(hw6_board_setup, board_setup00) {
  board *b = board_setup();
  piece wn = {WHITE,KNIGHT};
  cr_assert(GP1piece_eq(b->squares[0],&wn));
  GP1board_free(b);
}

Test(hw6_piece_at, piece_at00) {
  board *b = GP1empty();
  loc l = {'C',2};
  cr_assert(piece_at(b,l)==NULL);
  GP1board_free(b);
}

Test(hw6_occupied, occupied00) {
  board *b = GP1empty();
  loc l = {'A',1};
  cr_assert(!occupied(b,l));
  GP1board_free(b);
};

Test(hw6_unoccupied, unoccupied00) {
  board *b = GP1empty();
  loc l = {'D',3};
  cr_assert(unoccupied(b,l));
  GP1board_free(b);
}

Test(hw6_pieces_of, pieces_of00) {
  board *b = GP1empty();
  cr_assert(pieces_of(b,WHITE)==NULL && pieces_of(b,BLACK)==NULL);
  GP1board_free(b);
}

Test(hw6_adjacent_knight, adjacent_knight00) {
  loc l = {'C',3};
  loc_list *ks = adjacent_knight(l);
  cr_assert(GP1locs_len(ks)==8);
  GP1locs_free(ks);
}

Test(hw6_adjacent_guard, adjacent_guard00) {
  loc l = {'C',3};
  loc_list *ks = adjacent_guard(l);
  cr_assert(GP1locs_len(ks)==8);
  GP1locs_free(ks);
}

Test(hw6_adjacent_ortho, adjacent_ortho00) {
  loc l = {'C',3};
  loc_list *ks = adjacent_ortho(l);
  cr_assert(GP1locs_len(ks)==4);
  GP1locs_free(ks);
}

Test(hw6_protected_knight_at, protected_knight_at00) {
  board *b = GP1empty();
  loc l = {'C',1};
  cr_assert(!protected_knight_at(b,l));
  GP1board_free(b);
}

Test(hw6_legal_knight, legal_knight00) {
  board *b = GP1empty();
  move m = {{'A',1},{'A',2}};
  cr_assert(!legal_knight(b,m,WHITE));
  GP1board_free(b);
}

Test(hw6_legal_guard, legal_guard00) {
  board *b = GP1empty();
  move m = {{'A',1},{'A',2}};
  cr_assert(!legal_guard(b,m,WHITE));
  GP1board_free(b);
}

Test(hw6_available_moves, available_moves00) {
  board *b = GP1empty();
  cr_assert(available_moves(b,BLACK)==NULL);
  GP1board_free(b);
}

Test(hw6_available_fortifications, available_fortifications00) {
  board *b = GP1empty();
  cr_assert(available_fortifications(b,BLACK)==NULL);
  GP1board_free(b);
}

Test(hw6_apply_move, apply_move00) {
  board *b = GP1empty();
  int o;
  move m = {{'C',1},{'C',2}};
  piece *p = apply_move(b,m,WHITE,&o);
  cr_assert(o==ERR_NO_PIECE);
  if (p) {free(p);} // this is unnecessary, but suppresses compiler warning
                    // about unused variable
  GP1board_free(b);
}

Test(hw6_fortify, apply_fortify00) {
  board *b = GP1empty();
  int o;
  loc l = {'C',99};
  fortify(b,l,BLACK,&o);
  cr_assert(o==ERR_BAD_LOCATION);
  GP1board_free(b);
}
