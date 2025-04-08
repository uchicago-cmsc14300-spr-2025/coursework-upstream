#include <criterion/criterion.h>
#include <stdio.h>
#include "hw2.h"

// ======== tests

Test(hw2_count_color, count_color00)
{
  rgb colors[] = {0X00000000, 0XF0000000, 0XF0000000};
  cr_assert(count_color(0XF0000000, colors, 3)==2);
}

Test(hw2_negate_colors, negate_colors00)
{
  rgb colors[]  = {0XFF00FF00, 0X00FF0000};
  rgb negated[] = {0X00FF0000, 0XFF00FF00};
  negate_colors(colors,2);
  cr_assert(colors[0]==negated[0] && colors[1]==negated[1]);      
}

Test(hw2_stretch, stretch00)
{
  rgb colors[] = {0, 0XF0F0F000};
  rgb *s = stretch(colors, 2);
  cr_assert(s[0]==0 && s[1]==0 && s[2]==0XF0F0F000 && s[3]==0XF0F0F000);
}

Test(hw2_max_green, max_green00)
{
  rgb colors[] = {0XFFEEBB00, 0XFFDDAA00};
  cr_assert(max_green(colors,2)==0XEE);
}

Test(hw2_connect_rgb_arrays, connect_rgb_arrays00)
{
  rgb colors1[] = {0, 0X0000BB00};
  rgb colors2[] = {0XFF000000};
  rgb *c = connect_rgb_arrays(colors1,2,colors2,1);
  cr_assert(c[0]==0 &&
	    c[1]==0X0000BB00 &&
	    c[2]==0XFF000000);
}

Test(hw2_sift_up, sift_up00)
{
  datetime dates[] = {20250401000000, 20250101000000, 20250201000000};
  sift_up(dates, 1);
  cr_assert(dates[0]==20250101000000 &&
	    dates[1]==20250401000000 &&
	    dates[2]==20250201000000);
}

Test(hw2_sift_down, sift_down00)
{
  datetime dates[] = {20290401000000, 20250101000000, 20250201000000};
  sift_down(dates, 0, 2);
  cr_assert(dates[0]==20250101000000 &&
	    dates[1]==20290401000000 &&
	    dates[2]==20250201000000);
}

Test(hw2_heapsort_dates, heapsort_dates00)
{
  datetime dates[] = {20200101000000, 20180101000000, 20140101000000};
  heapsort_dates(dates,3);
  cr_assert(dates[0]==20140101000000 &&
	    dates[1]==20180101000000 &&
	    dates[2]==20200101000000);
}

Test(hw2_distinct_dates, distinct_dates00)
{
  datetime dates[] = {20240101000000, 20240101000000};
  int n;
  datetime *ds = distinct_dates(dates,2,&n);
  cr_assert(n==1 && ds[0]==20240101000000);
}

Test(hw2_weekdays, weekdays00)
{
  int n;
  datetime *w = weekdays(20250405000000, 20250408000000, &n);
  cr_assert(n==2 &&
	    w[0]==20250407000000 &&
	    w[1]==20250408000000);
}

Test(hw2_weekends, weekends00)
{
  int n;
  datetime *w = weekends(20250405000000, 20250408000000, &n);
  cr_assert(n==2 &&
	    w[0]==20250405000000 &&
	    w[1]==20250406000000);
}

Test(hw2_nonprimes, nonprimes00)
{
  int n;
  unsigned int a[] = {1,2,3,4,5,6,7,8,9,99};
  unsigned int *np = nonprimes(a,10,&n);
  cr_assert(n==6 &&
	    np[0]==1 &&
	    np[1]==4 &&
	    np[2]==6 &&
	    np[3]==8 &&
	    np[4]==9 &&
	    np[5]==99);
}

