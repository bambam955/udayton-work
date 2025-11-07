#include <math.h>
#include <stdio.h>
#include <linux/time.h>

// 10. Prime Numbers

int isPrimeToHalf(int a)
{
    // Test for even-ness using bitmath instead of modulus.
    // This is a little shortcut before the loop starts.
    if (a & 1 == 0)
    {
        return 0;
    }

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
    // Test for even-ness using bitmath instead of modulus.
    // This is a little shortcut before the loop starts.
    if (a & 1 == 0)
    {
        return 0;
    }

    for (int i = 2; i <= sqrt(a); ++i)
    {
        if (a % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

/*
 * We really only need to test the ODD numbers from 1-10000, since all even numbers after 2 are
 * by definition composite. We do so with an early return in the isPrime() functions.
 * Also, we need to start at 2, since 1 is not prime.
 *
 * The performance improvement between going to n/2 versus sqrt(n) is significant.
 * In my WSL environment, time taken when going to n/2 was 3945 microseconds,
 * versus 394 microseconds when going to sqrt(n), which is about 1/10 the time.
 */

void findPrimes()
{
    puts("\n10. PRIME NUMBERS TESTING");

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 2; i <= 10000; ++i)
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
    for (int i = 2; i <= 10000; ++i)
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
