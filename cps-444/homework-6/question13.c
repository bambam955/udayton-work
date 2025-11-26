#include <stdio.h>

void input_n_chars(char arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        scanf("%c", arr + i);
    }
}

void question13()
{
    char arr[10];
    input_n_chars(arr, 10);
    puts(arr);
}
