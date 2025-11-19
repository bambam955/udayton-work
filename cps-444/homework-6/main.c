#include <stdio.h>
#include "mydefs.h"

#define NUM_QUESTIONS 16

int main()
{
    for (int i = 0; i < NUM_QUESTIONS; ++i)
    {
        printf("\n========== QUESTION %d ==========\n", i + 1);
        questions[i]();
    }
    return 0;
}
