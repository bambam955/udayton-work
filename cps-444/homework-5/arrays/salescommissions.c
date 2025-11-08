#include <stdio.h>

// Solution for problem 16 of the arrays section.

int main(void)
{
    // Gross sales input
    int sales = 0;
    // Computed salary
    int salary = 0;
    // Counters for each of the 9 salary ranges
    int range[9] = {0};

    // Input loop
    puts("Enter gross sales for each salesperson (-1 to end):");
    while (1)
    {
        printf("Enter sales in dollars: ");
        scanf("%d", &sales);

        // Any negative value means the user is done inputting sales amounts.
        if (sales < 0)
            break;

        // Compute the commission-based salary.
        // Make sure to truncate to int.
        salary = 200 + (int)(0.09 * sales);

        // Determine which range to increment.
        // Anything over $1000 goes in the last counter.
        // All other counters 200-999 are in $100 increments.
        if (salary >= 1000)
            range[8]++;
        else
            range[(salary - 200) / 100]++;
    }

    // Output results as a table.
    printf("\n|----------------|-------|\n");
    printf("| %-14s | %-5s |\n", "Salary Range", "Count");
    printf("|----------------|-------|\n");
    for (int i = 0; i < 8; ++i)
    {
        char label[20];
        sprintf(label, "%d-%d", i * 100 + 200, i * 100 + 299);
        printf("| %-14s | %-5d |\n", label, range[i]);
    }
    printf("| $1000 and over | %-5d |\n", range[8]); // Separate line because range is different
    printf("|----------------|-------|\n");
}
