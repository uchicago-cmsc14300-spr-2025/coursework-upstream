#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "knightshift.h"
#include "computer-player.h"
#include "knightshell.h"

piece *quick_piece(char c)
{
  switch (c) {
  case 'k': return piece_new(WHITE,KNIGHT);
  case 'g': return piece_new(WHITE,ROYAL_GUARD);
  case 'f': return piece_new(WHITE,FORTRESS);
  case 'K': return piece_new(BLACK,KNIGHT);
  case 'G': return piece_new(BLACK,ROYAL_GUARD);
  case 'F': return piece_new(BLACK,FORTRESS);
  }
  fprintf(stderr,"(quick_piece) bad arg\n");
  exit(1);
}

// quick_board is to facilitate testing
// ranks needs to be 8 5-char strings exactly
// k, g, f for white knight, guard, fortress
// K, G, F for black
// . (dot character) for empty
// GIGO if arg is ill-formed in any way
board *quick_board(char *ranks[])
{
  board *b = board_empty();
  for (int r=0; r<8; ++r) {
    int rank = 8-r;
    for (int f=0; f<5; ++f) {
      if (ranks[r][f]!='.') {
	char file = 'A'+f;
	loc k = {file,rank};
	put_piece(b,quick_piece(ranks[r][f]),k);
      }
    }
  }
  return b;
}

int even(int n)
{
  return n%2==0;
}

char *square_str(piece *p, loc k)
{
  if (!p) 
    return even(k.file+k.rank)?"~":" ";
  if (p->color==WHITE) {
    if (p->type==KNIGHT) return UNICODE_KNIGHT_WHITE;
    if (p->type==ROYAL_GUARD) return UNICODE_KING_WHITE;
    if (p->type==FORTRESS) return UNICODE_ROOK_WHITE;
  }
  if (p->color==BLACK) {
    if (p->type==KNIGHT) return UNICODE_KNIGHT_BLACK;
    if (p->type==ROYAL_GUARD) return UNICODE_KING_BLACK;
    if (p->type==FORTRESS) return UNICODE_ROOK_BLACK;
  }
  fprintf(stderr,"(square_str) bug\n");
  exit(1);
}

void board_show(board *b)
{
  for (int rank=8; rank>=1; --rank) {
    printf("-----------\n");
    for (char file='A'; file<='E'; ++file) {
      loc l = {file,rank};
      putchar('|');
      piece *p = piece_at(b,l);
      printf("%s",square_str(p,l));
    }
    printf("| %d\n",rank);
  }
  printf("-----------\n");
  printf(" A B C D E \n");
}

int isfile(char c)
{
  return 'A'<=c && c<='E';
}

int isrank(char c)
{
  return '1'<=c && c<='8';
}

int is_fortify_cmd(char *canon)
{
  if (strlen(canon)!=5)
      return 0;
  return canon[0]=='F' &&
    isfile(canon[1]) &&
    isrank(canon[2]) &&
    isfile(canon[3]) &&
    isrank(canon[4]);
}

int is_move_cmd(char *canon)
{
  int n = strlen(canon);
  if (n==4 || n==5) {
    if (n==5 && canon[0]=='M')
      ++canon;
    return isfile(canon[0]) &&
      isrank(canon[1]) &&
      isfile(canon[2]) &&
      isrank(canon[3]);
  }
  else
    return 0;
}

// remove all spaces and make all characters uppercase
// ex: turns "M b1   C6  " into "MB1C6"
char *canonicalize(char *line)
{
  int n = strlen(line);
  char *canon = malloc(n+1);
  int j=0;
  for (int i=0; i<n; ++i) {
    if (isnumber(line[i]))
      canon[j++]=line[i];
    else if (isalpha(line[i]))
      canon[j++]=toupper(line[i]);
  }
  canon[j]='\0';
  return canon;
}

command parse(char *s)
{
  command cmd;
  char *canon = canonicalize(s);
  int len = strlen(canon);
  if (len==0)
    cmd.category = UNKNOWN;
  else if (is_move_cmd(canon)) {
    cmd.category = MOVE;
    int cursor = len==4?0:1;
    cmd.src.file = canon[cursor++];
    cmd.src.rank = canon[cursor++]-'0';
    cmd.dst.file = canon[cursor++];
    cmd.dst.rank = canon[cursor]-'0';
  } else if (is_fortify_cmd(canon)) {
    cmd.category = FORTIFY;
    cmd.src.file = canon[1];
    cmd.src.rank = canon[2]-'0';
  } else if (canon[0]=='H') {
    cmd.category = HELP;
  } else if (canon[0]=='Q') {
    cmd.category = QUIT;
  } else {
    cmd.category = UNKNOWN;
  }
  free(canon);
  return cmd;
}

void command_show(command cmd)
{
  if (cmd.category==FORTIFY)
    fprintf(stderr,"FORTIFY %c%d\n",cmd.src.file,cmd.src.rank);
  else if (cmd.category==MOVE)
    fprintf(stderr,"MOVE %c%d to %c%d\n",
	   cmd.src.file,cmd.src.rank,
	   cmd.dst.file,cmd.dst.rank);
  else if (cmd.category==HELP)
    fprintf(stderr,"HELP\n");
  else if (cmd.category==QUIT)
    fprintf(stderr,"QUIT\n");
  else
    fprintf(stderr,"UNRECOGNIZED\n");
}

void help_show()
{
  printf("\n");
  printf("-------- HELP --------\n");
  printf("M: move; ex: M A1 B1\n");
  printf("F: fortify, ex: F A1\n");
  printf("H: display (these) help messages\n");
  printf("Q: quit\n");
  printf("(commands are case insensitive and ignore spaces)\n");
  printf("(the M/m can be omitted from a move)\n");
  printf("\n");
}

void error_show(int outcome)
{
  printf("ERROR: ");
  switch (outcome) {
  case ERR_NO_PIECE:
    printf("no piece at the source location\n");
    break;
  case ERR_PIECE_TYPE:
    printf("wrong piece type for selection\n");
    break;
  case ERR_BAD_MOVE:
    printf("illegal move\n");
    break;
  case ERR_FRIENDLY:
    printf("destination space contains friendly piece\n");
    break;
  case ERR_BAD_LOCATION:
    printf("bad location (off the board)\n");
    break;
  default:
    printf("Hmm...some miscellaneous problem, maybe a bug (outcome=%d)\n",
	   outcome);
    break;
  }
}

void prompt(color turn)
{
  printf("-> %s's turn ('H' for help)\n",turn==WHITE?"White":"Black");
  printf(" > ");
}

int handle_victory(board *b)
{
  int g = game_over(b);
  if (g)
    printf(">>>VICTORY<<<\n");
  if (g==VICTORY_WHITE_TWO_FORTRESSES)
    printf("White wins with two fortresses!\n");
  else if (g==VICTORY_WHITE_THREE_CAPTURES)
    printf("White wins with three captures!\n");
  else if (g==VICTORY_BLACK_TWO_FORTRESSES)
    printf("Black wins with two fortresses!\n");
  else if (g==VICTORY_BLACK_THREE_CAPTURES)
    printf("Black wins with three captures!\n");
  return g;
}

void random_black_turn(board *b)
{
  int o = 0;
  move *m = random_move(b,BLACK);
  if (!m) {
    // check for fortifications
    loc_list *fs = available_fortifications(b,BLACK);
    if (!fs)
      perror("black can't identify any move or fortification");
    else {
      fortify(b,fs->k,BLACK,&o);
      if (o)
	perror("something went wrong with black's move");
    }
  } else {
    piece *p = apply_move(b,*m,BLACK,&o);
    if (o)
      perror("something went wrong with black's move");
    if (p)
      printf(">>>CAPTURE<<<\n");
  }
  board_show(b);
}

void black_turn(board *b, int(*heuristic)(board*))
{
  int o = 0;

  enum choice c;
  loc *f = NULL;
  move *m = NULL;

  printf("(thinking...)\n");

  int score = minimax(heuristic,b,5,BLACK,&c,&f,&m);
  //int score = minimax(&custom_heuristic,b,5,BLACK,&c,&f,&m);
  //int score = minimax(&base_heuristic,b,5,BLACK,&c,&f,&m);

  score = score*1;
  
  if (c==CHOICE_FORT) {
    char *fstr = loc_tos(*f);
    printf("Black fortifies %s\n",fstr);
    free(fstr);
    fortify(b,*f,BLACK,&o);
    if (o) 
      perror("something went wrong with black's fortification");
    board_show(b);
  } else if (c==CHOICE_MOVE) {
    char *ms = move_tos(*m);
    printf("Black chooses move %s\n",ms);
    free(ms);
    piece *p = apply_move(b,*m,BLACK,&o);
    if (o)
      perror("something went wrong with black's move");
    if (p)
      printf(">>>CAPTURE<<<\n");
    board_show(b);
  } else if (c==CHOICE_NONE) {
    perror("computer player bug: black chose no move");
  }
}

int main(int argc, char *argv[])
{
  char *line = NULL;
  size_t size = 0;
  ssize_t nread;
    
  board *b = board_setup();
  color turn = WHITE;
  int o = 0;

  int(*heuristic)(board*) = &base_heuristic;
  if (argc>1 && tolower(argv[1][0]=='c')) {
    printf("(using custom_heuristic)\n");
    heuristic = &custom_heuristic;
  } else
    printf("(using base_heuristic)\n");
  
  board_show(b);
  prompt(turn);

  while ((nread = getline(&line, &size, stdin)) != -1) {

    command cmd = parse(line);

    o=0;
    if (cmd.category==QUIT) {
      printf("Bye!\n");
      exit(0);
    } else if (cmd.category==HELP) {
      help_show();
      prompt(turn);
      continue;
    } else if (cmd.category==FORTIFY) {
      fortify(b,cmd.src,turn,&o);
      board_show(b);
    } else if (cmd.category==MOVE) {
      move m = {cmd.src,cmd.dst};
      piece *p = apply_move(b,m,turn,&o);
      board_show(b);
      if (p) 
	printf(">>>CAPTURE<<<\n");
    } else if (cmd.category==UNKNOWN || 1) { // default
      printf("unrecognized command\n");
      prompt(turn);
      continue;
    }

    if (o) {
      printf("!!!!!!!!\n");
      error_show(o);
      board_show(b);
      prompt(turn);
      continue;
    } else { 
      turn = (turn==WHITE)?BLACK:WHITE;
    }

    if (handle_victory(b))
      exit(0);

    //random_black_turn(b);
    black_turn(b,heuristic);
    if (handle_victory(b))
      exit(0);    

    turn = WHITE;
    prompt(turn);
  }
  
  free(line);
  return 0;  
}

