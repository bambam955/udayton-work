#include <stdio.h>
#include "mydefs.h"

void testBasicMath()
{
    // Hypotenuse testing
    puts("1. HYPOTENUSE TESTING");
    printf("a=3, b=4. Hypotenuse: %.2f\n", hypotenuse(3, 4));
    printf("a=5, b=12. Hypotenuse: %.2f\n", hypotenuse(5, 12));
    printf("a=8, b=15. Hypotenuse: %.2f\n", hypotenuse(8, 15));

    // IntegerPower testing
    puts("\n2. INTEGER POWER TESTING");
    for (int i = 2; i < 5; ++i)
    {
        printf("%d^%d = %d\n", i, i + 2, integerPower(i, i + 2));
    }

    // Multiples testing
    puts("\n3. MULTIPLES TESTING");
    for (int i = 24; i <= 36; i += 3)
    {
        printf("%d is%s a multiple of %d\n", i, multiple(i / 4, i) ? "" : " not", i / 4);
    }

    // Asterisks square testing
    puts("\n4. ASTERISKS SQUARE TESTING");
    for (int i = 1; i <= 4; ++i)
    {
        asterisks(i);
    }

    // Square of any character testing
    puts("\n5. SQUARE ANY CHARACTER TESTING");
    charSquare(5, '~');
    charSquare(2, '&');

    // Calculate time in seconds between two times.
    puts("\n6. TIME IN SECONDS TESTING");
    printf("Seconds between 1:32:37 and 3:02:37  : %d\n", timeSeconds(3, 2, 37) - timeSeconds(1, 32, 37));
    printf("Seconds between 12:34:17 and 3:09:18 : %d\n", timeSeconds(3, 9, 18) - timeSeconds(12, 34, 17));

    // Minimum of 3 floating-point nums testing
    puts("\n8. MIN THREE FLOATS TESTING");
    printf("min(3.5,8.9,1.1)    = %.1f\n", minThree(3.5, 8.9, 1.1));
    printf("min(14.5,90.1,90.2) = %.1f\n", minThree(14.5, 90.1, 90.2));
}

void testTemps()
{
    puts("\n7. TEMPERATURE CONVERSIONS TESTING");
    puts("|---------------|---------|\t|------------|------------|");
    puts("| Fahrenheit to | Celsius |\t| Celsius to | Fahrenheit |");
    puts("|---------------|---------|\t|------------|------------|");
    for (int f = 32; f <= 212; ++f)
    {
        int c = f - 32;
        printf("| %-13d | %-7d |", f, celsius(f));

        if (c <= 100)
        {
            printf("\t| %-10d | %-10d |", c, fahrenheit(c));
        }
        else if (c == 101)
        {
            printf("\t|------------|------------|");
        }

        printf("\n");
    }
    puts("|---------------|---------|");
}
