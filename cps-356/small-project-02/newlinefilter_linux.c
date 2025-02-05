#ifndef NEWLINE_FILTER_C
#define NEWLINE_FILTER_C

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 512

static void filterInput(const char *str, int strlen, char *output);

int main(int argc, char *argv[])
{
    // Create variables.
    // The buffers can both be created once because we clear them out after each use.
    int bytesRead = 0;
    char buffer[BUF_SIZE];
    char filtered[BUF_SIZE];
    while (1)
    {
        // Read from stdin. Works the same as any other file.
        bytesRead = read(0, &buffer, sizeof(buffer));
        if (bytesRead < 1)
            break;

        // Process the input.
        filterInput(buffer, bytesRead, filtered);
        // Write the processed input back to stdout.
        write(1, filtered, strlen(filtered));

        // Clear the buffers. The strlen function will stop at the first null character it sees.
        // Without this step, the previous round of input stays in the buffer and will be outputted erroneously.
        // For example, if I ran "fjfjfjfj" and then "aaaa" I would get "aaaa\njfj".
        for (int i = 0; i < bytesRead; ++i)
        {
            buffer[i] = filtered[i] = '\0';
        }
    }

    return 0;
}

static void filterInput(const char *str, int strlen, char *output)
{
    // This flag will be used iteration to determine if
    // another newline should be added to the output string or not.
    bool wasLastCharNewline = false;
    // The length of the output will probably be different than the length of the input
    // so we track the two separately to avoid empty holes in the output buffer.
    int outputlen = 0;
    for (int i = 0; i < strlen; ++i)
    {
        char c = str[i];

        // Do not add another newline to output if it would be second consecutive newline.
        if (c == '\n' && wasLastCharNewline)
        {
            continue;
        }

        // For any other case besides the above, add the character to the output string.
        output[outputlen] = c;
        ++outputlen;
        // Save whether this character was a newline for the next go-round.
        wasLastCharNewline = (c == '\n');
    }
}

#endif
