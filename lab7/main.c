#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "htbl.h"

#define DEFAULT_SIZE   10 /* default hash table size */
#define MAX_LINE_LEN 1024 /* maximum length for lines read from stdin */

/* display usage message */
void usage(char *exec_name)
{
  fprintf(stderr,"Usage: %s [OPTIONS]\n", exec_name);
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"  -b      \tuse lousy hash function\n");
  fprintf(stderr,"  -s <num>\tuse <num> (positive int) table size\n");
}

/* zero out trailing newlines in s */
void clip_newlines(char *s)
{
  int n = strlen(s)-1;
  while (n>=0 && s[n]=='\n')
    s[n--]='\0';
}

/* set options in the two out parameters */
void parse_opts(int argc, char *argv[], int *bad_hash, int *sz)
{
  char c;
  while ((c=getopt(argc,argv,"bs:"))!=-1) {
    switch (c) {
    case 'b':
      *bad_hash = 1;
      break;
    case 's':
      *sz = atoi(optarg);
      if (*sz<1) {
	fprintf(stderr,"%s error: nonpositive table size %d\n",*argv,*sz);
	exit(1);
      }
      break;
    case '?':
      usage(*argv);
      exit(1);
    }
  }
}

void htbl_info(htbl *t)
{
  printf("\nThe hash table has %i buckets with %i entries (load factor %lg).\n",
	 t->n_buckets, 
	 htbl_n_entries(t),
	 htbl_load_factor(t));
  printf("\nThe bucket with the most items in it contains %d items.\n",
	 htbl_max_bucket(t));
  /* test hash table membership */
  /* "aardvark" is not in the names file; "brunocharlie" is */
  printf("\ntesting htbl_member:\n");
  printf("membership of name \"aardvark\" : %i\n", htbl_member("aardvark",t));
  printf("membership of name \"brunocharlie\"    : %i\n", htbl_member("brunocharlie",t));
}

/* main:
 * read in strings from standard input,
 * build hash table,
 * display hash table and a few statistics */
int main(int argc, char *argv[])
{
  char buffer[MAX_LINE_LEN];
  int bad = 0;
  int sz  = DEFAULT_SIZE;
  parse_opts(argc,argv,&bad,&sz);
  htbl *t = htbl_new(bad?&bad_hash:&good_hash,sz);
  while (!feof(stdin)) {
    buffer[0] = '\0';
    fgets(buffer,MAX_LINE_LEN,stdin);
    clip_newlines(buffer);
    if (strlen(buffer)>0)
      htbl_insert(buffer,t);
  }
  htbl_show(t);
  htbl_info(t);
  htbl_free(t);
  return 0;
}
