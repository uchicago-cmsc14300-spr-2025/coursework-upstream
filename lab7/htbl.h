#ifndef _HTBL_H
#define _HTBL_H

/* a bucket is a linked list, each of whose entries contains a string and its hash */

typedef struct bucket bucket;
struct bucket {
  char *string;
  unsigned long int hash;
  bucket *next;
};
/* By convention, the empty bucket is NULL. */

typedef struct hash_table htbl;
struct hash_table {
  unsigned long int(*hash)(char*); /* a function pointer for
                                    * the specific hash function to use */
  bucket **buckets; /* an array of buckets */
  unsigned int n_buckets;
};

/* === bucket operations === */

/* bucket_cons : (char*, unsigned long, bucket*) -> bucket* */
/* build new list with given string at the head */
/* note: copy the given string to the list (deep copy) */
bucket *bucket_cons(char *s, unsigned long int hash, bucket *b);

/* bucket_size : bucket* -> int */
/* return the number of strings in the given bucket */
unsigned int bucket_size(bucket *b);

/* bucket_show : bucket* -> <void> */
/* print a representation of the linked list to stdout */
void bucket_show(bucket *b);

/* bucket_free : bucket* -> <void> */
/* free the list nodes and all strings pointed to as well (deep free) */
void bucket_free(bucket *b);

/* === hashing === */

/* good_hash : char -> unsigned long */
/* compute hash code for given string */
/* see writeup for algorithm */
unsigned long int good_hash(char *s);

/* bad_hash : char -> unsigned long */
/* implement this however you like, as long as it's bad */
unsigned long int bad_hash(char *s);

/* === hash table operations === */

/* htbl_new : (string -> unsigned long) int -> htbl* */
/* allocate space for a new hash table of given size */
/* save function pointer for specific hash function to use */
/* all buckets initially empty */
htbl *htbl_new(unsigned long int(*h)(char*), unsigned int sz);

/* htbl_n_entries : htbl* -> unsigned int */
/* return the total number of entries in all buckets */
unsigned int htbl_n_entries(htbl *t);

/* htbl_load_factor : htbl* -> float */
/* The load factor is the mean number of elements per bucket. */
double htbl_load_factor(htbl *t);

/* htbl_max_bucket : htbl* -> unsigned int */
/* Report the number of items in the fullest bucket. */
/* (Ideally, the max bucket has 1 item in it.) */
unsigned int htbl_max_bucket(htbl *t);

/* htbl_insert : (char*, htbl*) -> void */
/* add string s to hash table t */
/* no special treatment for duplicates, just insert them again */
void htbl_insert(char *s, htbl *t);

/* htbl_member : (char*, htbl*) -> int */
/* test membership of given string in given table */
/* note: use hashes for fast comparison; see comments in writeup */
int htbl_member(char *s, htbl *t);

/* htbl_show : htbl* -> <void> */
/* print a representation of the hash table to stdout */
void htbl_show(htbl *t);

/* htbl_free : htbl* -> <void> */
void htbl_free(htbl *t);

#endif /* _HTBL_H */
