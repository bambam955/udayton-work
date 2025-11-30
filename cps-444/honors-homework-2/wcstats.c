#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydefs.h"

// Simple macro to find the maximum of two values.
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// This struct holds the wc stats for a string of bytes.
// Note that all stats are counted regardless of options,
// and then the output is filtered based on options.
// This could be a spot for future improvement.
struct file_wc_stats
{
    int newlines;
    int words;
    int bytes;
};

// This flag checks whether the counter is currently on a word or not.
// It needs to be static/outside the function because we read from the file
// with no regard to word boundaries, so it's possible that the previous
// input buffer ended in the middle of a word, and we don't want to double-count.
static bool currently_in_word = false;
// Count up the wc stats for a string of given length. This function
// assumes that the input has no textual meaning, i.e. it does not use
// textual boundaries such as null characters when counting.
struct file_wc_stats count_stats_for_str(const char *input, int len)
{
    struct file_wc_stats stats = {0, 0, 0};

    // Count bytes first.
    stats.bytes = len;

    // Count newlines based on \n,
    // and words using isspace to detect whitespace.
    // The loop condition is designed to not rely on null characters.
    for (const char *p = input; p < input + len; ++p)
    {
        if (*p == '\n')
            stats.newlines++;

        if (isspace((unsigned char)*p))
        {
            currently_in_word = false;
        }
        else if (!currently_in_word)
        {
            stats.words++;
            currently_in_word = true;
        }
    }

    return stats;
}
// Add two wc stats structs together. Struct b is added to a.
void add_stats(struct file_wc_stats *a, const struct file_wc_stats *b)
{
    a->newlines += b->newlines;
    a->words += b->words;
    a->bytes += b->bytes;
}

// This global is used to have a consistent "cell size" for each value
// in the table produced when the stats are displayed.
static int table_cell_fmt_len = 0;
// This function converts a file's stats to a string according to
// the command options and cell size.
void print_file_wc_stats(struct file_wc_stats *stats, struct wc_stat_flags *options)
{
    if (options->newlines)
    {
        printf("%*d ", table_cell_fmt_len, stats->newlines);
    }
    if (options->words)
    {
        printf("%*d ", table_cell_fmt_len, stats->words);
    }
    if (options->bytes)
    {
        printf("%*d ", table_cell_fmt_len, stats->bytes);
    }

    // Trim the last space off of the end.
    printf("\b");
}

// Figure out the string length of each value in the stats for a file and determine
// if any of the stats are large enough as a string to increase the table cell size.
int determine_fmt_size(struct file_wc_stats *w, struct wc_stat_flags *flags)
{
    int max_len = 0;

    if (flags->newlines)
    {
        char buf[64];
        sprintf(buf, "%d", w->newlines);
        max_len = MAX(max_len, (int)strlen(buf));
    }

    if (flags->words)
    {
        char buf[64];
        sprintf(buf, "%d", w->words);
        max_len = MAX(max_len, (int)strlen(buf));
    }

    if (flags->bytes)
    {
        char buf[64];
        sprintf(buf, "%d", w->bytes);
        max_len = MAX(max_len, (int)strlen(buf));
    }

    return max_len;
}

int output_file_stats(const char *filenames[], int len, struct wc_stat_flags *options)
{
    // If the amount of files is 0 then read from stdin.
    const bool is_reading_stdin = (len == 0);

    // This array will contain the stats for each file so that they can be outputted at the end.
    struct file_wc_stats all_stats[len];
    // These will be the aggregate stats.
    struct file_wc_stats total_stats = {0, 0, 0};

    char buf[512];

    // If we are supposed to read from stdin then do that.
    // A lot of the output operations are similar but have to be done separately.
    if (is_reading_stdin)
    {
        // For reading from stdin, use fgets. It's more suited to reading text.
        struct file_wc_stats curr = {0, 0, 0};
        while (fgets(buf, sizeof(buf), stdin) != NULL)
        {
            const struct file_wc_stats this_stats = count_stats_for_str(buf, strlen(buf));
            add_stats(&curr, &this_stats);
        }

        // We only have to keep track of totals since there is only one "file".
        total_stats = curr;
        // For some reason 7 is the default cell size when reading from stdin.
        table_cell_fmt_len = MAX(7, determine_fmt_size(&curr, options));

        print_file_wc_stats(&total_stats, options);
        puts(""); // Finish the line
    }
    else
    {
        // For normal operation, iterate through each file in the given array
        // and count up stats for it.
        for (int i = 0; i < len; ++i)
        {
            // Open the file.
            FILE *f = fopen(filenames[i], "r");
            if (f == NULL)
            {
                fprintf(stderr, "wc: %s: could not open file", filenames[i]);
                return EXIT_FAILURE;
            }

            struct file_wc_stats curr = {0, 0, 0};
            int bytes_read = 0;
            // Continue to read data from the file (not as text, but as binary)
            // until there is no more data to be read.
            while ((bytes_read = fread(buf, sizeof(char), sizeof(buf), f)) != 0)
            {
                // Sum up stats for the read data and append them to the stats for the file.
                const struct file_wc_stats this_stats = count_stats_for_str(buf, bytes_read);
                add_stats(&curr, &this_stats);
            }
            fclose(f);

            // Save the file's stats to the array for all files, then
            // aggregate with the total stats.
            all_stats[i] = curr;
            add_stats(&total_stats, &curr);

            // Recalculate the size for table cells.
            table_cell_fmt_len = MAX(table_cell_fmt_len, determine_fmt_size(&curr, options));
        }

        // Recalculate the table cell size one more time using the total stats.
        // It's possible that the totals will be an order of magnitude greater
        // and require wider columns.
        table_cell_fmt_len = MAX(table_cell_fmt_len, determine_fmt_size(&total_stats, options));

        // Once all files have been processed, it is time to output the per-file table.
        for (int i = 0; i < len; ++i)
        {
            print_file_wc_stats(&all_stats[i], options);
            printf(" %s\n", filenames[i]);
        }

        // Finally, if there was more than one file, output the total stats
        // at the bottom of the table.
        if (len > 1)
        {
            print_file_wc_stats(&total_stats, options);
            puts(" total");
        }
    }

    return EXIT_SUCCESS;
}
