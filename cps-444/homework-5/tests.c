#include <stdio.h>
#include "mydefs.h"

void testAll()
{
    puts("1. HYPOTENUSE TESTING");
    printf("a=3, b=4. Hypotenuse: %.2f\n", hypotenuse(3, 4));
    printf("a=5, b=12. Hypotenuse: %.2f\n", hypotenuse(5, 12));
    printf("a=8, b=15. Hypotenuse: %.2f\n", hypotenuse(8, 15));

    puts("\n2. INTEGER POWER TESTING");
    for (int i = 2; i < 5; ++i)
    {
        printf("%d^%d = %d\n", i, i + 2, integerPower(i, i + 2));
    }

    puts("\n3. MULTIPLES TESTING");
    for (int i = 24; i <= 36; i += 3)
    {
        printf("%d is%s a multiple of %d\n", i, multiple(i / 4, i) ? "" : " not", i / 4);
    }

    puts("\n4. ASTERISKS SQUARE TESTING");
    for (int i = 1; i <= 4; ++i)
    {
        asterisks(i);
    }

    puts("\n5. SQUARE ANY CHARACTER TESTING");
    charSquare(5, '~');
    charSquare(2, '&');

    puts("\n6. TIME IN SECONDS TESTING");
    printf("Seconds between 1:32:37 and 3:02:37  : %d\n", timeSeconds(3, 2, 37) - timeSeconds(1, 32, 37));
    printf("Seconds between 12:34:17 and 3:09:18 : %d\n", timeSeconds(3, 9, 18) - timeSeconds(12, 34, 17));

    testTemps();

    puts("\n8. MIN THREE FLOATS TESTING");
    printf("min(3.5,8.9,1.1)    = %.1f\n", minThree(3.5, 8.9, 1.1));
    printf("min(14.5,90.1,90.2) = %.1f\n", minThree(14.5, 90.1, 90.2));

    testPerfects();

    findPrimes();

    puts("\n11. REVERSING DIGITS TESTING");
    for (int i = 1234; i < 1000000; i *= 3)
    {
        printf("%d reversed is %d\n", i, reversedValue(i));
    }

    puts("\n12. GREATEST COMMON DIVISOR TESTING");
    int nums[5][2] = {{6, 8}, {8, 9}, {60, 120}, {48, 72}, {678, 24}};
    for (int i = 0; i < 5; ++i)
    {
        printf("GCD of %d and %d is: %d\n", nums[i][0], nums[i][1], gcd(nums[i][0], nums[i][1]));
    }

    puts("\n13. QUALITY POINTS TESTING");
    double grades[5] = {95, 71.3, 47.0, 80.1, 60.9};
    for (int i = 0; i < 5; ++i)
    {
        printf("Grade %.1f receives %d quality points\n", grades[i], qualityPoints(grades[i]));
    }
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

void testPerfects()
{
    puts("\n9. PERFECT NUMBERS TESTING");
    for (int i = 1; i <= 1000; ++i)
    {
        if (isPerfect(i))
        {
            printFactors(i);
        }
    }

    // Test some really big numbers.
    for (int i = 1000; i <= 1000000000; i = i * 2 + 1234)
    {
        printf("Testing big number %d...\n", i);
        if (isPerfect(i))
        {
            printFactors(i);
        }
    }
}
