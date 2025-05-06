#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htbl.h"

unsigned long int good_hash(char *s)
{
  fprintf(stderr,"todo: good_hash\n");
  exit(1);
}

unsigned long int bad_hash(char *s)
{
  fprintf(stderr,"todo: bad_hash\n");
  exit(1);
}

htbl *htbl_new(unsigned long int(*h)(char*), unsigned int sz)
{
  fprintf(stderr,"todo: htbl_new\n");
  exit(1);
}

unsigned int htbl_n_entries(htbl *t)
{
  fprintf(stderr,"todo: htbl_n_entries\n");
  exit(1);
}

double htbl_load_factor(htbl *t)
{
  fprintf(stderr,"todo: htbl_load_factor\n");
  exit(1);
}

unsigned int htbl_max_bucket(htbl *t)
{
  fprintf(stderr,"todo: htbl_max_bucket\n");
  exit(1);
}

void htbl_insert(char *s, htbl *t)
{
  fprintf(stderr,"todo: htbl_insert\n");
  exit(1);
}

int htbl_member(char *s, htbl *t)
{
  fprintf(stderr,"todo: htbl_member\n");
  exit(1);
}

void htbl_show(htbl *t)
{
  fprintf(stderr,"todo: htbl_show\n");
  exit(1);
}

void htbl_free(htbl *t)
{
  fprintf(stderr,"todo: htbl_free\n");
  exit(1);
}
