#include <criterion/criterion.h>
#include <math.h>
#include <stdio.h>
#include "hw0.h"

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

// -------- f2k

Test(hw0_f2k, f2k00)
{
  double k = f2k(32.0);
  cr_assert(within(TOL,k,273.15));
}

// -------- k2f

Test(hw0_k2f, k2f00)
{
  double f = k2f(0.0);
  cr_assert(within(TOL,f,-459.67));
}

// -------- hemishell_volume

Test(hw0_hvol, hvol00)
{
  cr_assert(within(TOL,hemishell_volume(10.0,1.0),567.58107));
}

// -------- hemishell_surface

Test(hw0_hsurf, hsurf00)
{
  cr_assert(within(TOL,hemishell_surface(10.0,1.0),1196.9468));
}

