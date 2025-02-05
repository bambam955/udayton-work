#ifndef LETTER_FILTER_C
#define LETTER_FILTER_C

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

static void filterInput(const char *str, int strlen, char* output)
{
    int outputlen = 0;
    for (int i = 0; i < strlen; ++i)
    {
        char c = str[i];
        // Convert lowercase to uppercase, then append.
        if (97 <= c && c <= 122)
        {
            output[outputlen] = (c - 32);
            ++outputlen;
        }
        // Filter whitespace characters to only be newlines.
        else if ((9 <= c && c <= 13) || c == 32)
        {
            output[outputlen] = '\n';
            ++outputlen;
        }
        // Filter out special characters and numbers altogether.
        else if ((33 <= c && c <= 64) ||
                 (91 <= c && c <= 96) ||
                 (123 <= c && c <= 126))
        {
            continue;
        }
        // For all other characters, just add to the output normally.
        else 
        {
            output[outputlen] = c;
            ++outputlen;
        }
    }
}

#endif
