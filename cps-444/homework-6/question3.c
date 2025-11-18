#include <stdio.h>
#include "printers.h"

int largest_val_int(int arr[], int len)
{
    int max = arr[0];
    for (int i = 1; i < len; ++i)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void question3()
{
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr2[] = {21, 23, 25, 27, 3, 5, 7, 9};

    print_arr_int("Array 1", arr1, 8);
    printf("Max of arr1: %d\n", largest_val_int(arr1, 8));

    print_arr_int("Array 2", arr2, 8);
    printf("Max of arr2: %d\n", largest_val_int(arr2, 8));
}
