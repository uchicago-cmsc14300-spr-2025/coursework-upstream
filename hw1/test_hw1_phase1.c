#include <criterion/criterion.h>
#include <math.h>
#include <stdio.h>
#include "hw1.h"

// ======== constants

const double TOL = 0.001;
// TOL is an abbreviation for "tolerance"

// ======== helper functions

int within(double epsilon, double a, double b)
{
  return fabs(a-b)<=epsilon;
}

// ======== tests

// (you can add additional tests as you see fit)

// --- datetime

Test(hw1_datetime, valid_datetime00)
{
  cr_assert(valid_datetime(20250401175332));
}

Test(hw1_datetime, day_before00)
{
  cr_assert(day_before(20251019123456)==20251018123456);
}

Test(hw1_datetime, day_after00)
{
  cr_assert(day_after(20251019123456)==20251020123456);
}

Test(hw1_datetime, earlier00)
{
  cr_assert(earlier(20250101121212,20250201121212));
}

Test(hw1_datetime, later00)
{
  cr_assert(later(20250101121212,20240508123212));
}

// --- rgb

Test(hw1_rgb, rgb_negate00)
{
  cr_assert(rgb_negate(0XFF11FF00)==0X00EE0000);
}

Test(hw1_rgb, luminance00)
{
  cr_assert(within(TOL,luminance(0),0.0));
}

Test(hw1_rgb, rgb_grayscale00)
{
  cr_assert(rgb_grayscale(0)==0);
}

// --- bit exercises

Test(hw1_bits, count_ones00)
{
  cr_assert(count_ones(3)==2);
}

Test(hw1_bits, count_zeroes00)
{
  cr_assert(count_zeroes(3)==30);
}

Test(hw1_bits, bits_differ00)
{
  cr_assert(bits_differ(1,3)==1);
}

// -- miscellaneous

Test(hw1_sphere, sphere_contains00)
{
  cr_assert(sphere_contains(0.0,0.0,0.0,1.0,
			    0.1,0.1,0.1,
			    0.2,0.2,0.2));
}

Test(hw1_integrals, f_integral00)
{
  cr_assert(within(TOL,f_integral(0.0,1.0,0.1),1.2375));
}

Test(hw1_integrals, g_integral00)
{
  cr_assert(within(TOL,g_integral(0.0,1.0,0.1),3.801388098));
}
