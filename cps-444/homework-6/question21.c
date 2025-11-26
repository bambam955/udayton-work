#include <stdio.h>
#include "question20.h"

int days_to_month(int month_index)
{
    int total = 0;
    for (int i = 0; i <= month_index - 1; ++i)
    {
        total += months[i].num_days;
    }
    return total;
}

void question21()
{
    printf("Enter a month number: ");
    int index;
    scanf("%d", &index);
    printf("Number of days through month %d: %d\n", index, days_to_month(index));
}
