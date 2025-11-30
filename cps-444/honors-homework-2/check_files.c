#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int check_valid_files(const char *filenames[], int len)
{
    struct stat sb;
    int status;
    for (int i = 0; i < len; ++i)
    {
        const char *path = filenames[i];
        status = stat(path, &sb);
        if (status == 0)
        {
            // Path exists, but is a directory, which is invalid input
            if (S_ISDIR(sb.st_mode))
            {
                // It's a directory
                fprintf(stderr, "wc: %s: Is a directory\n", path);
                return EXIT_FAILURE;
            }
            else
            {
                // Path exists and is a file.
                continue;
            }
        }
        else
        {
            if (errno == ENOENT)
            {
                // File/Directory does not exist.
                fprintf(stderr, "wc: %s: No such file or directory\n", path);
            }
            else
            {
                // No idea what this error is. Just print a general message.
                fprintf(stderr, "wc: %s: an error occurred\n", path);
            }

            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
