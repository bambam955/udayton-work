#ifndef SMALL_PROJECT_00
#define SMALL_PROJECT_00

#include <fcntl.h>
#include <stdio.h>
#include <windows.h>

// If this macro is defined then the program will output all files it reads, i.e. verbose mode.
// Comment it out to hide debugging.
// #define VERBOSE_MODE
// Define the size of the buffer used for reading from files.
#define BUF_SIZE 4192

int main(long argc, char* argv[])
{
    // Output how many files were passed in to be read.
    printf("Processing %ld files...", argc - 1);

    // Initialize character counters.
    long countU = 0, countD = 0, countOthers = 0;

    // Loop through the filenames passed in as arguments.
    // We start with index 1 because the first "argument" is actually the name of the program. i.e. ./countUD.
    for (long i = 1; i < argc; i++)
    {
        // Open the next file in read-only mode since we don't need to modify it.
        int fd = open(argv[i], O_RDONLY);
        // Handle the possibility that the file doesn't exist. We don't want to read nonexistent files.
        if (fd == -1)
        {
#ifdef VERBOSE_MODE
            printf("No file found with name \'%s\', skipping to next file.\n", argv[i]);
#endif
            continue; // Skip to the next given file.
        }

#ifdef VERBOSE_MODE
        printf("Reading file \'%s\' ...\n", argv[i]);
#endif

        // Initialize the buffer that each byte of each file will be written to.
        // We use an array of chars so that we can avoid calling read() for every single byte.
        // This of course increases the space complexity but dramatically increases the speed of the program.
        char buf[BUF_SIZE] = { 0 };
        int bytesRead = 0;
        while (1)
        {
            // Attempt to read BUF_SIZE bytes (each equal to one ASCII character) from the opened file.
            // If there are no bytes left to read then exit the loop.
            bytesRead = read(fd, &buf, BUF_SIZE);
            if (bytesRead < 1)
                break;
            // Determine the value of each read character and increment the relevant counter.
            // Make sure to ignore all possible whitespace characters.
            for (int j = 0; j < (bytesRead > BUF_SIZE ? BUF_SIZE : bytesRead); j++)
            {
                switch (buf[j])
                {
                case 'U':
                    countU++; break;
                case 'D':
                    countD++; break;
                case '\n':
                case '\r':
                case '\t':
                case '\v':
                case '\f':
                case ' ':
                    break;
                default:
                    countOthers++; break;
                }
            }
        }
        // Close the opened file and output progress.
        close(fd);
#ifdef VERBOSE_MODE
        if (i + 1 == argc)
            printf("Finished reading file \'%s\'.\n", argv[i]);
        else
            printf("Finished reading file \'%s\', moving to next file.\n", argv[i]);
#endif
    }

    // Output the totals of each counter to the proper text streams.
    // TODO: should I use write(1, ...) and write(2, ...) for printing to the console?
    printf("Found %ld U's and %ld D's, total %ld\n", countU, countD, (countU + countD));
    fprintf(stderr, "Found %ld other characters\n", countOthers);

    // Return the proper exit code.
    return (countU > 0 || countD > 0) ? 0 : 1;
}

#endif
