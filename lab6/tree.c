#include "tree.h"

tree *tree_new(int n, tree *l, tree *r)
{
  tree *new_tree = (tree*)malloc(sizeof(tree));
  if (new_tree==NULL) {
    fprintf(stderr,"error (tree_new): malloc failed\n");
    exit(1);
  }
  new_tree->root=n;
  new_tree->lsub=l;
  new_tree->rsub=r;
  return new_tree;
}

tree *tree1(int n)
{
  return tree_new(n,NULL,NULL);
}

void tree_free(tree *t)
{
  if (t!=NULL)
    free(t);
}

void tree_show(FILE *f, tree *t)
{
  if (t==NULL)
    fprintf(f,"-");
  else {
    fprintf(f,"%d(",t->root);
    tree_show(f,t->lsub);
    fprintf(f,",");
    tree_show(f,t->rsub);
    fprintf(f,")");
  }
}
