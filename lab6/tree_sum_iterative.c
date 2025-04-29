#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "tree_stack.h"

int treesum(tree *t)
{
  if (!t)
    return 0;
  int sum=0;
  tree_stack *stk = tree_stack_new();
  push(t,stk);
  while (stk->trees!=NULL) {
    tree *curr = pop(stk);
    if (curr->rsub!=NULL)
      push(curr->rsub,stk);
    if (curr->lsub!=NULL)
      push(curr->lsub,stk);
    sum+=curr->root;
  }
  return sum;
}

int main(int argc, char *argv[])
{
  tree *t0 = NULL;
  tree *t1 = tree1(1);
  tree *t2 = tree_new(1,tree1(2),NULL);
  tree *t3 = tree_new(1,NULL,tree1(4));
  tree *t4 = tree_new(1,tree1(2),tree1(4));
  tree *t5 = tree_new(100,tree1(200),tree1(400));
  tree *ts[] = {t0,t1,t2,t3,t4,t5};
  int i;
  for (i=0; i<6; i++) {
    printf("t%d: ",i);
    tree_show(stdout,ts[i]);
    printf("\ntreesum: %d\n\n",treesum(ts[i]));
  }
  return 0;
}
