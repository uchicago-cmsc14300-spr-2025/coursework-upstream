#include <stdint.h>

typedef uint64_t datetime;
typedef uint32_t rgb;

// count the occurrences of the given color in array
// GIGO if array is NULL or if len is incorrect
int count_color(rgb c, rgb *colors, int len);

// negate all the colors in the array
// do not build an array; modify the array given
// GIGO if array is NULL or if len is incorrect
void negate_colors(rgb *colors, int len);

// return new array of twice the length, with each color appearing twice
// GIGO if arr is NULL or if len is incorrect
rgb *stretch(rgb *colors, int len);

// return the maximum green component of any color in array
// GIGO if array is NULL or len is not positive
uint8_t max_green(rgb *arr, int len);

// build new array that is all the colors in a followed by all the colors in b
// GIGO if a or b is NULL or either length incorrect
rgb *connect_rgb_arrays(rgb *a, int alen, rgb *b, int blen);

// sift up min-heap operation
// GIGO if array is NULL or pos is outside the array
void sift_up(datetime *dates, int pos);

// sift down min-heap operation
// GIGO if array is NULL, if pos is outside the array, or len is incorrect
void sift_down(datetime *dates, int pos, int len);

// in-place heapsort of datetime array
// perform in-place heapsort using sift operations
// GIGO if array is NULL or len is incorrect
void heapsort_dates(datetime *dates, int len);

// return an array of the distinct dates in an array of dates
// assume no particular order for array argument
// the return value must be in ascending order
// GIGO if dates is NULL or len is incorrect
datetime *distinct_dates(datetime *dates, int len, int *outlen);

// build array of dates of weekdays from start to end inclusive
// the time part of each datetime must be valid but is unconstrained
// return NULL and set outlen to 0 if there are no weekdays between dates
// return NULL and set outlen to 0 if end date before start date
datetime *weekdays(datetime start_incl, datetime end_incl, int *outlen);

// build array of dates of weekends from start to end inclusive
// the time part of each datetime must be valid but is unconstrained
// return NULL and set outlen to 0 if there are no weekends between dates
// return NULL and set outlen to 0 if end date before start date
datetime *weekends(datetime start_incl, datetime end_incl, int *outlen);

// construct new array, keeping all the nonprimes in the argument array
// report length in count
// if no nonprimes, return NULL and set count to 0
// GIGO if a is NULL or len is incorrect
unsigned int *nonprimes(unsigned int *a, int len, int *count);
