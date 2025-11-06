#include <stdio.h>

// 9. Perfect Numbers
int isPerfect(int a)
{
    // No odd numbers are perfect. We can return early.
    if (a % 2 != 0)
    {
        return 0;
    }

    int total = 1;
    for (int i = 2; i < a; ++i)
    {
        // If the sum of the factors found so far is already greater than the number itself,
        // it's clearly not a perfect number. Return early.
        if (total > a)
        {
            return 0;
        }

        // Add to the total if "i" is a factor.
        const int isFactor = a % i == 0;
        if (isFactor)
        {
            total += i;
        }
    }
    return total == a;
}

void printFactors(int a)
{
    printf("Factors of %d: ", a);
    for (int i = 1; i < a; ++i)
    {
        const int isFactor = a % i == 0;
        if (isFactor)
        {
            printf("%d,", i);
        }
    }
    puts("\b ");
}
