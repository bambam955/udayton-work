#include <stdio.h>

// Solution for problem 18 of the arrays section.

int main(void)
{
    // Store all of the previous entries.
    // This is the smallest possible array...we don't need to store 20 entries
    // because we never have to check against the 20th entry.
    int entries[19];
    int curr = 0;
    int isDuplicate = 0;

    // Input loop
    for (int i = 0; i < 20; ++i)
    {
        printf("Enter a number 10-100: ");
        scanf("%d", &curr);

        // Return on invalid input.
        if (curr < 10 || 100 < curr)
            return 1;

        // Save the latest entry.
        entries[i] = curr;

        // Figure out if the most recent entry was a duplicate.
        isDuplicate = 0;
        for (int j = 0; j < i; ++j)
        {
            if (entries[j] == curr)
            {
                isDuplicate = 1;
            }
        }

        // Print it out ONLY if it wasn't a duplicate.
        if (!isDuplicate)
        {
            printf("%d\n", curr);
        }
    }
}