#include "mydefs.h"

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
    testBasicMath();
    testTemps();
}
