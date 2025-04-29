#include "tree_stack.h"

tree_stack *tree_stack_new()
{
  tree_stack *stk = (tree_stack*)malloc(sizeof(tree_stack));
  if (stk==NULL) {
    fprintf(stderr,"error (tree_stack_new): malloc failed\n");
    exit(1);
  }
  stk->trees=NULL;
  return stk;
}

void push(tree *t, tree_stack *stk)
{
  stk->trees = tl_cons(t,stk->trees);
}

tree *pop(tree_stack *stk)
{
  if (stk->trees==NULL) {
    fprintf(stderr,"error (pop): empty\n");
    exit(1);
  }
  tree *t = stk->trees->t;
  stk->trees = stk->trees->next;
  return t;
}

void tree_stack_free(tree_stack *stk)
{
  free(stk);
}

void tree_stack_show(FILE *f, tree_stack *stk)
{
  fprintf(f,"stack (top at left): ");
  tl_show(f,stk->trees);
}
