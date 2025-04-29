#ifndef _TREE_STACK_H
#define _TREE_STACK_H

#include "tree.h"
#include "tree_list.h"

typedef struct _tree_stack tree_stack;

struct _tree_stack {
  tree_list *trees;
};

tree_stack *tree_stack_new();

void push(tree *t, tree_stack *stk);

tree *pop(tree_stack *stk);

void tree_stack_free(tree_stack *stk);

void tree_stack_show(FILE *f, tree_stack *stk);

#endif /* _TREE_STACK_H */
