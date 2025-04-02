#ifndef __HW1_H__

#include <stdint.h>

typedef unsigned char byte;
typedef uint64_t datetime; //YYYYMMDDHHMMSS
typedef uint32_t rgb;

// === datetime

// A datetime is a year, month, day, hour, minute, second
// representation of a moment in time as an integer of the form
// YYYYMMDDHHMMSS.

// By convention, January is month 1 up to December month 12.

// Hours go from 00 to 23, military style; minutes and seconds from 00
// to 59.

// For example, March 26, 2024 at 4:07:23PM is 20240326160723 as a
// datetime.

// Verify that the datetime is legitimate. For example, January the
// 49th (of any year) is not a legitimate datetime, nor is any
// datetime at 27 o'clock. Yes, the code must check for leap
// years. Helper functions recommended.
// GIGO if the date is prior to the 20th century.
int valid_datetime(datetime t);

// Return the datetime 24 hours before the given moment.
// GIGO if the date is prior to the 20th century.
// GIGO if the date is not valid.
datetime day_before(datetime t);

// Return the datetime 24 hours after the given moment.
// GIGO if the date is prior to the 20th century.
// GIGO if the date is not valid.
datetime day_after(datetime t);

// Return true if t1 is an earlier datetime than t2.
// GIGO if either date is prior to the 20th century.
// GIGO if either date is not valid.
int earlier(datetime t1, datetime t2);

// Return true if t1 is a later datetime than t2.
// GIGO if either date is prior to the 20th century.
// GIGO if either date is not valid.
int later(datetime t1, datetime t2);

// === rgb

// a packed rgb contains red in the highest byte, green in the
// second-highest byte, blue in third-highest byte, and 0 in the
// lowest byte. For example, the color (255,255,255) is represented as
// 11111111 11111111 11111111 00000000 as a prgb. We carry the fourth
// byte because there is no three-byte integer type.

// The negation of a color (r,g,b) is (255-r,255-g,255-b).
rgb rgb_negate(rgb c);

// The luminance (a measure of brightness) of an RGB color
// is 0.2126R + 0.7152G + 0.0722B. Higher luminance corresponds
// to greater brightness.
// To ensure the results of computing luminance are consistent with
// our tests, compute the _floor_ of the linear combination
// given above.
// Note that this means the luminance of (255,255,255) is 254.0 (wrong
// though that might seem).
double luminance(rgb c);

// The grayscale of a color is (m,m,m) where m is the luminance of the
// color. For example, since the luminance of (11,22,100) is 25.0, the
// grayscale counterpart is (25,25,25).
rgb rgb_grayscale(rgb c);

// === bit exercises

// Count the bits set to 1 in n.
byte count_ones(uint32_t n);

// Count the bits set to 0 in n.
byte count_zeroes(uint32_t n);

// Count the number of bits that differ, by position, in m and n.
byte bits_differ(uint32_t m, uint32_t n);

// === miscellaneous

// A sphere is represented by a center (cx, cy, cz) and a radius.
// A line segment (in three dimensions) is represented by
// its two endpoints a and b.
// Return true if the sphere strictly contains the line segment.
// GIGO if radius is nonpositive.
int sphere_contains(double cx, double cy, double cz, double r,
		    double ax, double ay, double az,
		    double bx, double by, double bz);

// Let f(x)=x^3 + x^2 + x.
// Compute the integral as a left Riemann sum from a (left) to
//   b (right) where each rectangle has width dx.
// In the sum, only include rectangles that fit within the
//   integral region (the right edge is allowed to be *at* b).
// GIGO if b<=a or dx<=0.
double f_integral(double a, double b, double dx);

// Let g(x)=sin(x)+2.
// Compute the integral as a left Riemann sum from a (left) to
//   b (right) where each rectangle has width dx.
// In the sum, only include rectangles that fit within the
//   integral region (the right edge is allowed to be *at* b).
// GIGO if b<=a or dx<=0.
double g_integral(double a, double b, double dx);

#endif
