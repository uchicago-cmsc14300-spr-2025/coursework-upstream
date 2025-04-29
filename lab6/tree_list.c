#include "tree_list.h"

tree_list *tl_cons(tree *t, tree_list *ts)
{
  tree_list *tl_new = (tree_list*)malloc(sizeof(tree_list));
  if (tl_new==NULL) {
    fprintf(stderr,"error (tl_cons): malloc failed\n");
    exit(1);
  }
  tl_new->t = t;
  tl_new->next = ts;
  return tl_new;
}

void tl_free(tree_list *ts)
{
  if (ts!=NULL) {
    tl_free(ts->next);
    free(ts);
  }
}

void tl_show(FILE *f, tree_list *ts)
{
  fprintf(f,"tree list:\n");
  while (ts) {
    fprintf(f,"  ");
    tree_show(f,ts->t);
    ts=ts->next;
  }
}
