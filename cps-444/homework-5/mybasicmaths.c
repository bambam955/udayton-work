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
    for (int i = 1; i < exponent; ++i)
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

// 7. Temperature Conversions
int celsius(int f)
{
    return (f - 32) * 5 / 9;
}

int fahrenheit(int c)
{
    return (c * 9 / 5) + 32;
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
