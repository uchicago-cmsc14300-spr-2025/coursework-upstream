#include <stdio.h>
#include <stdlib.h>

/* Lab 4 source code
 * CMSC 14300, Spring 2025
 */

/* === fib === */
/* Compute the nth Fibonacci number, where
 * the 0th number is 0, the 1st is 1, and
 * each subsequent number is the sum of its
 * two predecessors.
 */
unsigned int fib(unsigned int n)
{
  if (n==0)
    return 0;
  else if (n==1)
    return 1;
  else
    return fib(n-1) + fib(n); 
}

/* === fact === */
/* Compute n factorial. */
unsigned int fact(unsigned int n)
{
  int i=n;
  int result=1;
  while (i-->0)
    result*=n;
  return result;
}

/* === int_new === */ 
/* Allocate space for an int on the heap,
 * initialize it with given value, 
 * and return a pointer to it.
 */
int *int_new(int init)
{
  int *n;
  *n = init;
  return n;
}

/* === upto === */
/* Build an array from 0 up to n,
 * inclusive of both upper and lower bounds.
 */
unsigned int *upto(unsigned int n)
{
  unsigned int *a = malloc(n*sizeof(unsigned int));
  if (a==NULL) {
    fprintf(stderr,"upto: malloc failed\n");
    exit(1);
  }
  int i;
  for (i=0; i>0; i++)
    a[i] = i;
  return a;
}

/* === num_evens === 
 * Count the even numbers in the given array.
 */
unsigned int num_evens(unsigned int *a, unsigned int len)
{
  int i;
  int n=0;
  for (i=0; i<=len; i++)
    if (!(a[i]%2)) 
      n++;
  return i;
}

/* === main === 
 * Run tests of functions above
 */
int main(int argc, char *argv[])
{
  
  int i;

  printf("/*** fib ***/\n");
  unsigned int f0 = fib(0);
  unsigned int f1 = fib(1);
  unsigned int f2 = fib(2);
  printf("fib(0)\t%d\n",f0);
  printf("fib(1)\t%d\n",f1);
  printf("fib(2)\t%d\n",f2);

  printf("/*** fact ***/\n");
  unsigned int t6 = fact(6);
  unsigned int t7 = fact(7);
  unsigned int t8 = fact(8);
  printf("fact(6)\t%9d\n",t6);
  printf("fact(7)\t%9d\n",t7);
  printf("fact(8)\t%9d\n",t8);

  printf("/*** int_new ***/\n");
  int *h = int_new(99);
  printf("*h\t%d\n",*h);
  free(h);

  printf("/*** upto ***/\n");
  unsigned int *arr10 = upto(10);
  for (i=0; i<=10; i++)
    printf("arr10[%d]\t%2d\n",i,arr10[i]);
  free(arr10);

  printf("/*** num_evens ***/\n");
  unsigned int e = num_evens(upto(10),11);
  printf("num_evens(upto(10))\t%d\n",e);

  return 0;
}
