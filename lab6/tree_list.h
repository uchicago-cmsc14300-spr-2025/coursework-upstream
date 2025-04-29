#ifndef _TREE_LIST_H
#define _TREE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct _tree_list tree_list;

struct _tree_list {
  tree *t;
  tree_list *next;
};

tree_list *tl_cons(tree *t, tree_list *ts);

void tl_free(tree_list *ts);

void tl_show(FILE *f, tree_list *ts);

#endif /* _TREE_LIST_H */

