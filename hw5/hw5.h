#ifndef __HW5_H__
#define __HW5_H__

// ======== data definitions

// convention: empty list is represented by NULL
// convention: empty tree is represented by NULL

struct int_point {
  int x;
  int y;
};
typedef struct int_point point;

struct point_list {
  point p;
  struct point_list *next;
};
typedef struct point_list point_list;

struct double_point {
  double x;
  double y;
};
typedef struct double_point dpoint;

struct int_list {
  int n;
  struct int_list *next;
};
typedef struct int_list int_list;

struct tree {
  int root;
  struct tree *left;
  struct tree *right;
};
typedef struct tree tree;

// ======== function headers

// construct a new list node and point next to points
point_list *pl_cons(point p, point_list *points);

// return pointer to the nth node in the list (starting from 0th)
// return NULL if there is no nth node
point *pl_nth(unsigned int n, point_list *points);

// free the list completely (not just the head struct)
void pl_free(point_list *points);

// construct a heap-allocated string of this format:
// "(1,2):(3,5):nil"
// that is, the empty list is "nil" and each point is in "(x,y)"
// format, with elements separated by ":"
// HINT: write a helper function that concatenates two strings
char *pl_tos(point_list *points);

// return a pointer to the highest point in list (with greatest y coord)
// if there are multiple highest points, return any one of them
// return NULL if list is empty
point *pl_highest(point_list *points);

// the centroid is the point with mean x, mean y
// return NULL if the list is empty
dpoint *pl_centroid(point_list *points);

// add dx and dy to every point in list
void pl_nudge(int dx, int dy, point_list *points);

// the xspan of a point list is the max x coord minus the min x coord
// it is necessarily nonnegative
// return special value -1 if list is empty
int pl_xspan(point_list *points);

// construct a new tree with given root and pointing to subtrees
tree *tree_new(int r, tree *left, tree *right);

// free the tree completely (not just the root struct)
void tree_free(tree *t);

// count the number of nodes in the tree
unsigned int tree_size(tree *t);

// compute the height of the tree
// count the number of "levels" in the tree
// the empty tree has height 0 by definition
unsigned int tree_height(tree *t);

// construct the left-to-right fringe of leaves of the tree
// the fringe of the empty tree is the empty list
int_list *tree_fringe(tree *t);

// construct the preorder traversal of ints in the tree
int_list *tree_preorder(tree *t);

// construct the inorder traversal of ints in the tree
int_list *tree_inorder(tree *t);

// construct a new tree that is the mirror image of the given one
// the empty tree is its own mirror image
tree *tree_mirror(tree *t);

// square every number in the given tree
void tree_sqr(tree *t);

// compare two trees for semantic equality:
// same shape, same numbers at every position
int tree_eq(tree *t1, tree *t2);

// if the tree is arranged like a *duplicate-free* BST, return true
// return false otherwise
// the empty tree *is* a legitimate BST, as is any singleton tree
int bst(tree *t);

#endif
