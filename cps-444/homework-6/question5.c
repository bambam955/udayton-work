#include <stdio.h>
#include "printers.h"

double double_arr_range(double arr[], int len)
{
    double min = arr[0], max = arr[0];
    for (int i = 1; i < len; ++i)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    return max - min;
}

void question5()
{
    double arr1[] = {1.1, 2.1, 1.3, 2.3, 1.5, 2.5, 1.7, 2.7};
    double arr2[] = {21, 23, 25, 27, 3.2, 3.4, 3.6, 3.8};

    print_arr_double("Array 1", arr1, 8);
    printf("Range of arr1: %.1f\n", double_arr_range(arr1, 8));

    print_arr_double("Array 2", arr2, 8);
    printf("Range of arr2: %.1f\n", double_arr_range(arr2, 8));
}