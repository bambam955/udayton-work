#include <stdbool.h>

struct wc_stat_flags
{
    bool newlines;
    bool words;
    bool bytes;
};

int parse_cmd(int argc, char *argv[], struct wc_stat_flags *wc_flags, int *first_pos_arg_ind);
int check_valid_files(const char *filenames[], int len);
