#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "hw5.h"

const double TOL = 0.001;

int within(double epsilon, double a, double b)
{
  return fabs(a-b)<=epsilon;
}

int str_eq(char *s, char *t)
{
  int slen = strlen(s);
  if (slen!=strlen(t))
    return 0;
  for (int i=0; i<slen; ++i)
    if (s[i]!=t[i])
      return 0;
  return 1;      
}

int leaf(tree *t)
{
  return t && !t->left && !t->right;
}

// ======== tests

// NOTE: memory is *not* consistently freed in these tests

Test(hw5_pl_cons, pl_cons00) {
  point p = {1,2};
  point_list *ps = pl_cons(p,NULL);
  cr_assert(ps->p.x==1 && ps->p.y==2 && !ps->next);
}

Test(hw5_pl_nth, pl_nth00) {
  point p = {3,4};
  point_list *ps = pl_cons(p,NULL);
  point *q = pl_nth(0,ps);
  cr_assert(q->x==3&&q->y==4);
}

Test(hw5_pl_free, pl_free00) {
  // we can only test that this doesn't crash
  point p = {3,4};
  point_list *ps = pl_cons(p,NULL);
  pl_free(ps);
  cr_assert(1);
}

Test(hw5_pl_tos, pl_tos00) {
  point p = {9,7};
  point_list *ps = pl_cons(p,NULL);
  char *s = pl_tos(ps);
  cr_assert(str_eq(s,"(9,7):nil"));
}
  
Test(hw5_pl_highest, pl_highest00) {
  point p = {2,0};
  point_list *ps = pl_cons(p,NULL);
  point *h = pl_highest(ps);
  cr_assert(h->x==2&&h->y==0);
}

Test(hw5_pl_centroid, pl_centroid00) {
  point p = {2,3};
  point_list *ps = pl_cons(p,NULL);
  dpoint *c = pl_centroid(ps);
  cr_assert(within(TOL,2.0,c->x) && within(TOL,3.0,c->y));  
}

Test(hw5_pl_nudge, pl_nudge00) {
  point p = {1,2};
  point_list *ps = pl_cons(p,NULL);
  pl_nudge(4,8,ps);
  cr_assert(ps->p.x==5&&ps->p.y==10);
}
  
Test(hw5_pl_xspan, pl_xspan00) {
  cr_assert(pl_xspan(NULL)==-1);
}

Test(hw5_tree_new, tree_new00) {
  tree *t = tree_new(1,NULL,NULL);
  cr_assert(t->root==1 && !t->left && !t->right);
}

Test(hw5_tree_free, tree_free00) {
  // we can only test that this doesn't crash
  tree *t = tree_new(1,NULL,NULL);
  tree_free(t);
  cr_assert(1);
}

Test(hw5_tree_size, tree_size00) {
  tree *t = tree_new(1,NULL,NULL);
  cr_assert(tree_size(t)==1);
}

Test(hw5_tree_height, tree_height00) {
  tree *t = tree_new(1,NULL,NULL);
  cr_assert(tree_height(t)==1);
}

Test(hw5_tree_fringe, tree_fringe00) {
  tree *t = NULL;
  cr_assert(tree_fringe(t)==NULL);
}

Test(hw5_tree_preorder, tree_preorder00) {
  tree *t = tree_new(9,NULL,NULL);
  int_list *pre = tree_preorder(t);
  cr_assert(pre->n==9&&pre->next==NULL);  
}

Test(hw5_tree_inorder, tree_inorder00) {
  tree *t = tree_new(9,NULL,NULL);
  int_list *in = tree_inorder(t);
  cr_assert(in->n==9&&in->next==NULL);  
}

Test(hw5_tree_mirror, tree_mirror00) {
  tree *t = tree_new(3,NULL,NULL);
  tree *m = tree_mirror(t);
  cr_assert(t->root==m->root && leaf(t) && leaf(m));
}

Test(hw5_tree_sqr, tree_sqr00) {
  tree *t = tree_new(3,NULL,NULL);
  tree_sqr(t);
  cr_assert(t->root==9 && leaf(t));
}
  
Test(hw5_tree_eq, tree_eq00) {
  tree *t = tree_new(3,NULL,NULL);
  tree *u = tree_new(2,NULL,NULL);
  cr_assert(!tree_eq(t,u));
}

Test(hw5_bst, bst00) {
  tree *t = tree_new(3, tree_new(3, NULL, NULL), NULL);
  cr_assert(!bst(t));
}
