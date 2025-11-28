#include <stdio.h>
#include <stdlib.h>
#include "mydefs.h"

int main(int argc, char *argv[])
{
    struct wc_stat_flags stat_flags;
    int first_pos_arg = 0;
    const int res = parse_cmd(argc, argv, &stat_flags, &first_pos_arg);
    if (res != 0)
        exit(EXIT_FAILURE);

    if (first_pos_arg > 0)
    {
        const int num_files = argc - first_pos_arg;
        const char *filenames[num_files];
        for (int i = first_pos_arg; i < argc; ++i)
        {
            filenames[i - first_pos_arg] = argv[i];
        }

        check_valid_files(filenames, num_files);
    }

    exit(EXIT_SUCCESS);
}
