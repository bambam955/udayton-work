#include <math.h>
#include <stdio.h>
#include <linux/time.h>

// 10. Prime Numbers

int isPrimeToHalf(int a)
{
    for (int i = 2; i <= a / 2; ++i)
    {
        if (a % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

int isPrimeToSqrt(int a)
{
    for (int i = 2; i <= sqrt(a); ++i)
    {
        if (a % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

void findPrimes()
{
    puts("\n10. PRIME NUMBERS TESTING");

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 1; i <= 10000; i += 2)
    {
        if (isPrimeToHalf(i))
        {
            printf("%d,", i);
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);

    long ns = end.tv_nsec - start.tv_nsec;
    puts("\b ");
    printf("Time taken (microsecs) when going to half: %ld\n", ns / 1000);

    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 1; i <= 10000; i += 2)
    {
        if (isPrimeToSqrt(i))
        {
            printf("%d,", i);
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);

    ns = end.tv_nsec - start.tv_nsec;
    puts("\b ");
    printf("Time taken (microsecs) when going to sqrt: %ld\n", ns / 1000);
}
