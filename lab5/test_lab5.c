#include <criterion/criterion.h>
#include "lab5.h"

// streq is provided as a helper for tests below
int streq(char *s, char *t)
{
    unsigned int i = 0;
    // by policy, NULLs are not equal to anything, even other NULLs
    if (s == NULL || t==NULL) {
        return 0;
    }
    
    while (s[i] || t[i]) {
        if (s[i] != t[i]) {
            return 0;
        }
        i++;
    }
    
    return 1;
}

// len tests...

Test(lab5_len, len_0)
{
    cr_assert(len("") == 0);
}

// repeat_char tests...

Test(lab5_repeat_char, repeat_char_0)
{
    cr_assert(streq(repeat_char('x', 0), ""));
}

// count_char tests...

Test(lab5_count_char, count_char_0)
{
    cr_assert(count_char('a', "") == 0);
}

// locations_of tests...

Test(lab5_locations_of, locations_of_0)
{
    unsigned int n = 0;
    unsigned int *locs = locations_of('x', "", &n);
    cr_assert(n==0);
    free(locs);
}

