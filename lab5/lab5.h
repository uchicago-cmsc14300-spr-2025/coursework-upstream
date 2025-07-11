/* Lab5 function headers */

// Please note: in lab5, including string.h or any other string-utilities
// module is not allowed (so as not to trivialize the work)

// len consumes a char* and computes the length of the string pointed to
// it is *assumed* the given pointer is not NULL
// note: the final '\0' is not counted
// ex: len("ABCD") --> 4
unsigned int len(char* string);

// repeat_char builds a heap-allocated string
// consisting of n copies of the character c
// ex: repeat_char('w', 4) --> "wwww"
char* repeat_char(char c, unsigned int n);

// count_char counts the number of occurrences of the char in the string
// it is assumed the pointer is not NULL
// ex: count_char('a', "acbbc") --> 1
// ex: count_char('b', "acbbc") --> 2
// ex: count_char('c', "acbbc") --> 2
// ex: count_char('d', "acbbc") --> 0
unsigned int count_char(char c, char* string);

// locations_of returns an array of locations in the given string
// also, *n is set to the length of that array
// it is assumed both pointers are not NULL
// if the char doesn't appear, return an empty array and set *n to 0
// ex: locations_of('x', "abxdx") --> pointer to [2,4] and *n is 2
// ex: locations_of('a', "abxdx") --> pointer to [0] and *n is 1
// ex: locations_of('z', "abxdx") --> empty array and *n=0
unsigned int* locations_of(char c, char* string, unsigned int* n);
