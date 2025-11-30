#include <stdio.h>
#include <stdlib.h>
#include "mydefs.h"

int main(int argc, char *argv[])
{
    struct wc_stat_flags stat_flags;
    int first_pos_arg = 0;
    if (parse_cmd(argc, argv, &stat_flags, &first_pos_arg) != 0)
        exit(EXIT_FAILURE);

    if (first_pos_arg > 0)
    {
        const int num_files = argc - first_pos_arg;
        const char *filenames[num_files];
        for (int i = first_pos_arg; i < argc; ++i)
        {
            filenames[i - first_pos_arg] = argv[i];
        }

        if (check_valid_files(filenames, num_files) != 0)
            exit(EXIT_FAILURE);

        if (output_file_stats(filenames, num_files, &stat_flags) != 0)
            exit(EXIT_FAILURE);
    }
    else
    {
        if (output_file_stats(NULL, 0, &stat_flags) != 0)
            exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
