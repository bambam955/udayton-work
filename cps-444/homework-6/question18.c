#include <stdio.h>
#include <stdlib.h>

void question18()
{
    // Clear the input buffer.
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    // Get user inputs.
    printf("How many words do you wish to enter? ");
    int num_words = 0;
    scanf("%d", &num_words);
    printf("Enter %d words now: ", num_words);
    char *words[num_words];
    for (int i = 0; i < num_words; ++i)
    {
        words[i] = malloc(100);
        scanf("%s", words[i]);
    }
    puts("Here are your words:");
    for (int i = 0; i < num_words; ++i)
    {
        printf("%s\n", words[i]);
    }
}
