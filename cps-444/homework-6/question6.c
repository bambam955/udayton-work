#include "printers.h"

void reverse_arr_double(double arr[], int len)
{
    double tmp = 0;
    for (int i = 0; i < ((len + 1) / 2); ++i)
    {
        tmp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = tmp;
    }
}

void question6()
{
    double arr1[] = {1.1, 2, 1.3, 3, 1.5, 4, 1.7, 5};
    double arr2[] = {21, 23, 25, 27, 50.5, 3.2, 3.4, 3.6, 3.8};

    print_arr_double("Array 1", arr1, 8);
    reverse_arr_double(arr1, 8);
    print_arr_double("Array 1 reversed", arr1, 8);

    print_arr_double("Array 2", arr2, 9);
    reverse_arr_double(arr2, 9);
    print_arr_double("Array 2 reversed", arr2, 9);
}
