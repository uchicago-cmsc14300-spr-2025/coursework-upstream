#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "knightshift.h"

int moves_len(move_list *moves)
{
  int n=0;
  for (;moves;moves=moves->next) ++n;
  return n;
}

char *loc_tos(loc k)
{
  char buf[8] = {0};
  sprintf(buf,"%c%d",k.file,k.rank);
  return strdup(buf);
}

char *move_tos(move m)
{
  char buf[16] = {0};
  sprintf(buf,"[%c%d -> %c%d]",m.src.file,m.src.rank,m.dst.file,m.dst.rank);
  return strdup(buf);
}

int on_board(loc k)
{
  return 'A'<=k.file && k.file<='E' && 1<=k.rank && k.rank<=8;
}
 
loc loc_new(char file, char rank)
{
  loc k;
  k.file = file;
  k.rank = rank;
  return k;
}

loc *loc_dup(loc k)
{
  loc *d = malloc(sizeof(loc));
  d->file = k.file;
  d->rank = k.rank;
  return d;
}

move move_new(loc src, loc dst)
{
  move m;
  m.src = src;
  m.dst = dst;
  return m;
}

move *move_dup(move m)
{
  move *d = malloc(sizeof(move));
  d->src = m.src;
  d->dst = m.dst;
  return d;
}

piece *piece_new(color color, piece_type type)
{
  piece *p = malloc(sizeof(piece));
  p->color = color;
  p->type = type;
  return p;
}

piece *piece_dup(piece *p)
{
  return piece_new(p->color, p->type);
}

int loc_index(loc k)
{
  return (k.rank-1)*5+(k.file-'A');
}

unsigned int llen(loc_list *locs)
{
  int n=0;
  for (;locs;locs=locs->next)
    ++n;
  return n;
}

unsigned int mlen(move_list *moves)
{
  int n=0;
  for (;moves;moves=moves->next)
    ++n;
  return n;
}

void put_piece(board *b, piece *p, loc k)
{
  b->squares[loc_index(k)] = p;
}

piece *piece_at(board *b, loc k)
{
  return b->squares[loc_index(k)];
}

board *board_empty()
{
  board *b = malloc(sizeof(board));
  for (int i=0; i<40; ++i)
    b->squares[i] = NULL;
  return b;
}

void board_free(board *b)
{
  for (int i=0; i<40; ++i) {
    piece *p = b->squares[i];
    if (p)
      free(p);
  }
  free(b);
}

board *board_setup()
{
  board *b = board_empty();
  for (int file='A'; file<='E'; file++) {
    piece_type type = file=='C'?ROYAL_GUARD:KNIGHT;
    put_piece(b, piece_new(BLACK,type), loc_new(file,8));
    put_piece(b, piece_new(WHITE,type), loc_new(file,1));
  }
  return b;
}

int occupied(board *b, loc k)
{
  return piece_at(b,k)?1:0;
}

int unoccupied(board *b, loc k)
{
  return !piece_at(b,k);
}

loc_list *lcons(loc k, loc_list *locs)
{
  loc_list *new_list = malloc(sizeof(loc_list));
  new_list->k = k;
  new_list->next = locs;
  return new_list;
}

loc loc_nudge(loc k, char df, char dr)
{
  return loc_new(k.file+df,k.rank+dr);
}

loc_list *lcons_if(loc k, loc_list *locs)
{
  return on_board(k)?lcons(k,locs):locs;
}

loc_list *adjacent_knight(loc k)
{
  loc_list *locs = NULL;
  char dfs[] = {2,2,-2,-2,1,1,-1,-1};
  char drs[] = {1,-1,1,-1,2,-2,2,-2};
  for (int i=0; i<8; ++i)
    locs = lcons_if(loc_nudge(k,dfs[i],drs[i]),locs);
  return locs;
}

loc_list *adjacent_guard(loc k)
{
  loc_list *locs = NULL;
  char dfs[] = {1,1,1,-1,-1,-1,0,0};
  char drs[] = {1,-1,0,1,-1,0,1,-1};
  for (int i=0; i<8; ++i)
      locs = lcons_if(loc_nudge(k,dfs[i],drs[i]),locs);
  return locs;
}

loc_list *adjacent_ortho(loc k)
{
  loc_list *locs = NULL;
  char dfs[] = {1,-1,0,0};
  char drs[] = {0,0,1,-1};
  for (int i=0; i<4; ++i)
    locs = lcons_if(loc_nudge(k,dfs[i],drs[i]),locs);
  return locs;
}

loc_list *pieces_of(board *b, color curr)
{
  loc_list *locs = NULL;
  for (char f='A'; f<='E'; ++f) {
    for (char r=1; r<=8; ++r) {
      loc k = loc_new(f,r);
      piece *p = piece_at(b, k);
      if (p && p->color==curr)
	locs = lcons(k,locs);
    }
  }
  return locs;
}

int opp_protected(board *b, loc k, color curr)
{
  color opp = curr==WHITE?BLACK:WHITE;
  loc_list *orth = adjacent_ortho(k);
  for (;orth;orth=orth->next) {
    piece *g = piece_at(b,orth->k);
    if (g && g->type==ROYAL_GUARD && g->color==opp)
      return 1;
  }
  return 0;
}

int protected_knight_at(board *b, loc k)
{
  piece *p = piece_at(b,k);
  if (!p || p->type!=KNIGHT)
    return 0;
  loc_list *orth = adjacent_ortho(k);
  for (;orth;orth=orth->next) {
    piece *g = piece_at(b,orth->k);
    if (g && g->type==ROYAL_GUARD && g->color==p->color)
      return 1;
  }
  return 0;
}

int knight_shape(move m)
{
  int df = abs(m.src.file-m.dst.file);
  int dr = abs(m.src.rank-m.dst.rank);
  return (df==1&&dr==2)||(df==2&&dr==1);
}

int guard_shape(move m)
{
  int df = abs(m.src.file-m.dst.file);
  int dr = abs(m.src.rank-m.dst.rank);
  if (df==0 && dr==0)
    return 0;
  else
    return df<=1 && dr<=1;
}

int opp_knight_at(board *b, loc k, color curr)
{
  color opp = curr==WHITE?BLACK:WHITE;
  piece *p = piece_at(b,k);
  return p && p->type==KNIGHT && p->color==opp;
}

int legal_knight(board *b, move m, color curr)
{
  piece *p = piece_at(b,m.src);
  if (!p || p->type!=KNIGHT || p->color!=curr)
    return 0;
  if (!knight_shape(m))
    return 0;
  if (protected_knight_at(b,m.dst))
    return 0;
  return unoccupied(b,m.dst) || opp_knight_at(b,m.dst,curr);
}

int legal_guard(board *b, move m, color curr)
{
  piece *p = piece_at(b,m.src);
  if (!p || p->type!=ROYAL_GUARD || p->color!=curr)
    return 0;
  if (!guard_shape(m))
    return 0;
  if (opp_protected(b,m.dst,curr))
    return 0;
  // if we get this far, it's an unprotected space
  // check that it's either empty or has opp knight
  return unoccupied(b,m.dst) || opp_knight_at(b,m.dst,curr);  
}

move_list *mcons(move m, move_list *moves)
{
  move_list *new_list = malloc(sizeof(move_list));
  new_list->m = m;
  new_list->next = moves;
  return new_list;
}

move_list *available_moves(board *b, color curr)
{
  loc_list *locs = pieces_of(b,curr);
  move_list *moves = NULL;
  for (;locs;locs=locs->next) {
    piece *p = piece_at(b,locs->k);
    if (p) {
      if (p->type==KNIGHT) {
	loc_list *ks = adjacent_knight(locs->k);
	for (;ks;ks=ks->next) {
	  move m = {locs->k,ks->k};
	  if (legal_knight(b,m,curr))
	    moves = mcons(m,moves);
	}
      } else if (p->type==ROYAL_GUARD) {
	loc_list *ks = adjacent_guard(locs->k);
	for (;ks;ks=ks->next) {
	  move m = {locs->k,ks->k};
	  if (legal_guard(b,m,curr))
	    moves = mcons(m,moves);
	}
      }
    }
  }
  return moves;
}

void mfree(move_list *ms)
{
  if (ms) {
    mfree(ms->next);
    free(ms);
  }
}

void lshow(loc_list *locs) 
{
  while (locs) {
    fprintf(stderr,"%c%d:",locs->k.file,locs->k.rank);
    locs=locs->next;
  }
  fprintf(stderr,"nil\n");
}

void mshow(move_list *moves) 
{
  while (moves) {
    char *mstr = move_tos(moves->m);
    fprintf(stderr,"%s:",mstr);
    free(mstr);
    moves=moves->next;
  }
  fprintf(stderr,"nil\n");
}

loc_list *available_fortifications(board *b, color curr)
{
  loc_list *locs = NULL;
  char rank = curr==WHITE?8:1;
  for (char file='A'; file<='E'; ++file) {
    loc k = loc_new(file,rank);
    piece *p = piece_at(b,k);
    if (p && p->type==KNIGHT && p->color==curr)
      locs = lcons(k,locs);
  }
  return locs;
}

void do_move(board *b, move m)
{
  piece *p = piece_at(b,m.src);
  if (p) {
    put_piece(b,p,m.dst);
    put_piece(b,NULL,m.src);
  }
}

board *board_dup(board *b)
{
  board *new_board = malloc(sizeof(board));
  for (int i=0; i<40; ++i) {
    piece *p = b->squares[i];
    new_board->squares[i] = p?piece_dup(p):NULL;
  }
  return new_board;
}

board *do_move_new(board *b, move m)
{
  board *b2 = board_dup(b);
  do_move(b2,m);
  return b2;
}

board *do_fortify_new(board *b, loc k, color curr)
{
  int o=0;
  board *b2 = board_dup(b);
  fortify(b2,k,curr,&o);
  if (o) {
    fprintf(stderr,"(do_fortify_new) outcome %d\n",o);
    exit(1);
  }
  return b2;
}

piece *apply_move(board *b, move m, color curr, int *outcome)
{
  if (!on_board(m.src) || !on_board(m.dst)) {
    *outcome = ERR_BAD_LOCATION;
    return NULL;
  }
  piece *p = piece_at(b,m.src);
  if (!p) {
    *outcome = ERR_NO_PIECE;
    return NULL;
  }
  if (p->color!=curr) {
    *outcome = ERR_BAD_MOVE;
    return NULL;
  }
  piece *q = piece_at(b,m.dst);
  if (p->type==KNIGHT && legal_knight(b,m,curr)) {
    *outcome = 0;
    do_move(b,m);
    return q;
  } else if (p->type==ROYAL_GUARD && legal_guard(b,m,curr)) {
    *outcome = 0;
    do_move(b,m);
    return q;
  }
  *outcome = ERR_BAD_MOVE;
  return NULL;
}

void fortify(board *b, loc k, color curr, int *outcome)
{
  if (!on_board(k)) {
    *outcome = ERR_BAD_LOCATION;
    return;
  }    
  if ((curr==WHITE && k.rank!=8) || (curr==BLACK && k.rank!=1)) {
    *outcome = ERR_BAD_LOCATION;
    return;
  }
  piece *p = piece_at(b,k);
  if (!p) {
    *outcome = ERR_NO_PIECE;
    return;
  }
  if (p->type!=KNIGHT) {
    *outcome = ERR_PIECE_TYPE;
    return;
  }
  if (p->color!=curr) {
    *outcome = ERR_BAD_MOVE;
    return;
  }
  p->type = FORTRESS;
}

int game_over(board *b)
{
  fprintf(stderr,"TODO: game_over\n");
  exit(1);
}
