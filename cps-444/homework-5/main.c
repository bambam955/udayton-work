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

// 7. Temperature Conversions

// 8. Find the Minimum

// 9. Perfect Numbers

// 10. Prime Numbers

// 11. Reversing Digits

// 12. Greatest Common Divisor

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
}
