#include <stdio.h>
#include <math.h>

// 1. Hypotenuse calculations
double hypotenuse(double a, double b)
{
    return sqrt(a * a + b * b);
}

// 2. Exponentiation
int integerPower(int base, int exponent)
{
    int res = base;
    for (int i = 2; i <= exponent; ++i)
    {
        res *= base;
    }
    return res;
}

// 3. Multiples
int multiple(int a, int b)
{
    return b % a == 0 ? 1 : 0;
}

// 4. Square of Asterisks
void asterisks(int side)
{
    for (int i = 0; i < side; ++i)
    {
        for (int j = 0; j < side; ++j)
        {
            printf("*");
        }
        printf("\n");
    }
}

// 5. Displaying a Square of Any Character
void charSquare(int side, char filler)
{
    for (int i = 0; i < side; ++i)
    {
        for (int j = 0; j < side; ++j)
        {
            printf("%c", filler);
        }
        printf("\n");
    }
}

// 6. Time in Seconds
int timeSeconds(int hours, int mins, int secs)
{
    return (hours % 12 * 60 + mins) * 60 + secs;
}

// 8. Find the Minimum
double minThree(double a, double b, double c)
{
    double res = a;
    if (res > b)
    {
        res = b;
    }
    if (res > c)
    {
        res = c;
    }
    return res;
}

// 9. Perfect Numbers

// 10. Prime Numbers

// 11. Reversing Digits

// 12. Greatest Common Divisor
int gcd(int a, int b)
{
    int factorOfBoth = 1;
    int i = 1;
    while (factorOfBoth && i < a && i < b)
    {
        factorOfBoth = (a % i == 0) && (b % i == 0);
        ++i;
    }
    return i;
}

// 13. Quality Points for Student's Grades

// 14. Fibonacci

int main(void)
{
    // Hypotenuse testing
    printf("1: a=3, b=4. Hypotenuse: %.2f\n", hypotenuse(3, 4));
    printf("1: a=5, b=12. Hypotenuse: %.2f\n", hypotenuse(5, 12));
    printf("1: a=8, b=15. Hypotenuse: %.2f\n", hypotenuse(8, 15));

    // IntegerPower testing
    for (int i = 2; i < 5; ++i)
    {
        printf("%d^%d = %d\n", i, i + 2, integerPower(i, i + 2));
    }

    // Multiples testing
    for (int i = 24; i <= 36; i += 3)
    {
        printf("%d is%s a multiple of %d\n", i, multiple(i / 4, i) ? "" : " not", i / 4);
    }

    // Asterisks square testing
    for (int i = 1; i <= 4; ++i)
    {
        asterisks(i);
    }

    // Square of any character testing
    charSquare(5, '#');

    // Calculate time in seconds between two times.
    printf("Time difference 1: %d\n", timeSeconds(3, 2, 37) - timeSeconds(1, 32, 37));
    printf("Time difference 2: %d\n", timeSeconds(3, 2, 37) - timeSeconds(12, 32, 37));

    // Minimum of 3 floating-point nums testing
    printf("%.1f\n", minThree(3.5, 8.9, 1.1));
    printf("%.1f\n", minThree(14.5, 90.1, 90.2));
}
