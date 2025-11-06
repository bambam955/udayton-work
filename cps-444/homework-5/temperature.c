#include <stdio.h>

// 7. Temperature Conversions
int celsius(int f)
{
    return (f - 32) * 5 / 9;
}

int fahrenheit(int c)
{
    return (c * 9 / 5) + 32;
}

int main()
{
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