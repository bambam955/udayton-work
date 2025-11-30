#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydefs.h"

// Define the static help message.
static char *help_msg = "Usage: wc [OPTION]... [FILE]...\n"
                        "  or:  wc [OPTION]... --files0-from=F\n"
                        "Print newline, word, and byte counts for each FILE, and a total line if\n"
                        "more than one FILE is specified.  A word is a non-zero-length sequence of\n"
                        "printable characters delimited by white space.\n"
                        "\n"
                        "With no FILE, or when FILE is -, read standard input.\n"
                        "\n"
                        "The options below may be used to select which counts are printed, always in\n"
                        "the following order: newline, word, character, byte, maximum line length.\n"
                        "  -m, --chars   print the character counts\n"
                        "  -l, --lines   print the newline counts\n"
                        "  -w, --words   print the word counts\n"
                        "\n"
                        "  --help     display this help and exit";

int parse_cmd(int argc, char *argv[], struct wc_stat_flags *wc_flags, int *first_pos_arg_ind)
{
    static struct option long_options[] = {
        {"lines", no_argument, NULL, 'l'}, // return 'l' in switch case
        {"words", no_argument, NULL, 'w'}, // return 'w'
        {"chars", no_argument, NULL, 'm'}, // return 'm'
        {"help", no_argument, NULL, 'h'},  // return 'h'
        {0, 0, 0, 0},                      // required array terminator
    };

    // The short_options string matches the shorthand option values for the long_options array.
    const char *short_options = "lwmh";

    // Loop through all the options and parse them one by one.
    // Setting opterr=0 allows for full control of error messages for invalid options.
    opterr = 0;
    bool was_stat_option_given = false;
    while (1)
    {
        // Store the index of the long option that was just found.
        int option_index = 0;
        // Parse out the next option.
        int curr_opt = getopt_long(argc, argv, short_options, long_options, &option_index);

        // This is the sentinel value for the end of the options.
        if (curr_opt == -1)
            break;

        // Handlers for each short option.
        switch (curr_opt)
        {
        // Parse out the different stat flags.
        case 'l':
            wc_flags->newlines = true;
            was_stat_option_given = true;
            break;
        case 'w':
            wc_flags->words = true;
            was_stat_option_given = true;
            break;
        case 'm':
            wc_flags->bytes = true;
            was_stat_option_given = true;
            break;

        // Print help message.
        case 'h':
            puts(help_msg);
            exit(EXIT_SUCCESS);

        // Handle unknown options.
        case '?':
            // Check if the problematic argument started with "--" to identify it as a long option error.
            if (argv[optind - 1] != NULL && strncmp(argv[optind - 1], "--", 2) == 0)
            {
                fprintf(stderr, "wc: unrecognized option '%s'\n", argv[optind - 1]);
            }
            // Otherwise, check for a short option error.
            else if (optopt != 0)
            {
                fprintf(stderr, "wc: invalid option -- '%c'\n", optopt);
            }
            else
            {
                // If we get here then there was some sort of parsing error.
                fprintf(stderr, "wc: unknown or invalid argument.\n");
            }

            // Handles unknown options or missing arguments.
            fprintf(stderr, "Try 'wc --help' for more information.\n");
            return EXIT_FAILURE;

        default:
            // We should NEVER get here.
            abort();
        }
    }

    // If no stat options were given then the default is to show everything.
    if (!was_stat_option_given)
    {
        wc_flags->newlines = true;
        wc_flags->words = true;
        wc_flags->bytes = true;
    }

    // This variable will hold the starting index of the positional arguments
    // after all of the options have been parsed out.
    *first_pos_arg_ind = optind < argc ? optind : -1;

    return EXIT_SUCCESS;
}
