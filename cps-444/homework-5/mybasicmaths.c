#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

// 11. Reversing Digits
int reversedValue(int a)
{
    // First convert the integer to a string.
    // 20 characters will be plenty for a 32-bit integer.
    char str[20] = {0};
    sprintf(str, "%d", a);

    // Figure out how many characters the stringified integer uses.
    int lastDigitChar = 0;
    for (int i = 0; i < 20; ++i)
    {
        if (!isdigit(str[i]))
        {
            lastDigitChar = i - 1;
            break;
        }
    }

    // Add the digit characters one by one to the new string...in reverse.
    char newStr[20] = {0};
    for (int i = lastDigitChar; i >= 0; --i)
    {
        newStr[lastDigitChar - i] = str[i];
    }

    // Convert the reversed string to an integer and return the result.
    char *endPtr;
    long int num = strtol(newStr, &endPtr, 10);
    return (int)num;
}

// 12. Greatest Common Divisor
int gcd(int a, int b)
{
    int gcd = 1;
    for (int i = 1; i <= a && i <= b; ++i)
    {
        if (a % i == 0 && b % i == 0)
        {
            gcd = i;
        }
    }
    return gcd;
}
