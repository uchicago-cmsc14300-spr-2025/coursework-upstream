#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h> // for gettimeofday
#include "lab8.h"

// unsigned int luminance(struct rgb c);

// struct rgb grayscale(struct rgb c);

// struct image *read_image(FILE *f);

void grayscale_seq(struct image *img);

void grayscale_par(struct image *img, unsigned int n_threads);

