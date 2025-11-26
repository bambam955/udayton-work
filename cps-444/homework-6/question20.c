#include <stdio.h>
#include "question20.h"

struct month months[12] = {
    {"January", "Jan", 31, 1},
    {"February", "Feb", 28, 2},
    {"March", "Mar", 31, 3},
    {"April", "Apr", 30, 4},
    {"May", "May", 31, 5},
    {"June", "Jun", 30, 6},
    {"July", "Jul", 31, 7},
    {"August", "Aug", 31, 8},
    {"September", "Sep", 30, 9},
    {"October", "Oct", 31, 10},
    {"November", "Nov", 30, 11},
    {"December", "Dec", 31, 12},
};

void question20()
{
    printf("| %-9s | %-9s | %-9s | %-9s |\n", "Number", "Name", "Abbrev", "Num. Days");
    puts("| --------- | --------- | --------- | --------- |");
    for (int i = 0; i < 12; ++i)
    {
        printf("| %-9d | %-9s | %-9s | %-9d |\n",
               months[i].index, months[i].name, months[i].abbrev, months[i].num_days);
    }
}
