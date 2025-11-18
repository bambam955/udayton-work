#include <stdio.h>
#include "printers.h"

void copy_arr(double dest[], double src[], int len)
{
    for (int i = 0; i < len; ++i)
    {
        dest[i] = src[i];
    }
}

void copy_ptr(double dest[], double src[], int len)
{
    double *ptr = dest;
    for (int i = 0; i < len; ++i, ptr++)
    {
        *ptr = src[i];
    }
}

void copy_ptrs(double dest[], double src[], double *element_after)
{
    const int len = element_after - src;
    for (int i = 0; i < len; ++i)
    {
        dest[i] = src[i];
    }
}

void question2()
{
    double source[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double target1[5];
    double target2[5];
    double target3[5];

    // Copy arrays in 3 different ways.
    copy_arr(target1, source, 5);
    copy_ptr(target2, source, 5);
    copy_ptrs(target3, source, source + 5);

    // Print results.
    print_arr_double("Original", source, 5);
    print_arr_double("Target 1", target1, 5);
    print_arr_double("Target 2", target2, 5);
    print_arr_double("Target 3", target3, 5);
}
