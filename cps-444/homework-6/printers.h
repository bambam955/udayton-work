#ifndef _MY_PRINTERS_H
#define _MY_PRINTERS_H
#include <stdio.h>

static void print_arr_int(const char *label, int arr[], int len)
{
    printf("%s: ", label);
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", arr[i]);
    }
    puts("");
}

static void print_arr_double(const char *label, double arr[], int len)
{
    printf("%s: ", label);
    for (int i = 0; i < len; ++i)
    {
        printf("%.1f ", arr[i]);
    }
    puts("");
}

#endif
