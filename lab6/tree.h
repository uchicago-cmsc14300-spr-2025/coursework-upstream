#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _tree tree;

struct _tree {
  int root;
  tree *lsub;
  tree *rsub;
};

/* By convention, the empty tree is NULL. */

tree *tree_new(int n, tree *l, tree *r);

/* singleton constructor for trees */
tree *tree1(int n);

void tree_free(tree *t);

void tree_show(FILE *f, tree *t);

#endif /* _TREE_H */
