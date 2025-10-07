package main

import (
	"fmt"
	"os"
	"strings"

	"github.com/spf13/pflag"
)

// Create the set of flags for our wc command.
var fs = pflag.NewFlagSet("wc", pflag.ContinueOnError)
var lines = fs.BoolP("lines", "l", false, "print the newline counts")
var words = fs.BoolP("words", "w", false, "print the word counts")
var chars = fs.BoolP("chars", "m", false, "print the character counts")
var helpFlag = fs.Bool("help", false, "display this help and exit")

func init() {
	// Any flag-related error messages will be printed to stderr.
	fs.SetOutput(os.Stderr)

	fs.Usage = func() {
		if f := fs.Lookup("help"); f != nil {
			f.Hidden = true
		}
		var msg = `Usage: wc [OPTION]... [FILE]...
  or:  wc [OPTION]... --files0-from=F
Print newline, word, and byte counts for each FILE, and a total line if
more than one FILE is specified.  A word is a non-zero-length sequence of
printable characters delimited by white space.

With no FILE, or when FILE is -, read standard input.

The options below may be used to select which counts are printed, always in
the following order: newline, word, character, byte, maximum line length.`
		// The help message is printed to stdout.
		fs.SetOutput(os.Stdout)
		fmt.Println(msg)
		fs.PrintDefaults()
		fmt.Println("\n  --help     display this help and exit")
	}
}

func Execute() error {
	// If there is some sort of invalid option then print an error message and return early.
	err := fs.Parse(os.Args[1:])
	if err != nil {
		return checkInvalidOptions(err)
	}

	// Print the help message if the flag was passed.
	if *helpFlag {
		fs.Usage()
		return nil
	}

	fmt.Printf("%t %t %t\n", *lines, *words, *chars)
	return nil
}

func checkInvalidOptions(err error) error {
	var invalidOption string
	// If the erroneous flag is a shorthand flag (i.e. a one-letter abbreviation)
	// then the error will contain "shorthand flag". If the erroneous flag is a fully
	// described flag then the error will contain "unknown flag". We can use these
	// to get the error messages exactly right.
	if strings.Contains(err.Error(), "shorthand flag") {
		// An example error message might look something like this:
		// "unknown shorthand flag: 'a' in -asef"
		start := strings.Index(err.Error(), "'")
		if start != -1 {
			end := strings.Index(err.Error()[start+1:], "'")
			if end != -1 {
				invalidOption = err.Error()[start+1 : start+1+end]
			}
		}
		// For some reason wc has different error messages for shorthand and full-length flags.
		// Here we print "invalid option", down farther we use "unrecognized option".
		if invalidOption != "" {
			fmt.Fprintf(os.Stderr, "wc: invalid option -- '%s'\n", invalidOption)
		}
	} else if strings.Contains(err.Error(), "unknown flag") {
		// An example error message might look like this:
		// "unknown flag: --wawmlsefasef", which is much easier to parse.
		parts := strings.Fields(err.Error())
		if len(parts) > 0 {
			flagPart := parts[len(parts)-1]
			if strings.HasPrefix(flagPart, "--") {
				invalidOption = flagPart
			}
		}
		// Here is where we use "unrecognized option" as the error message to match the real command.
		if invalidOption != "" {
			fmt.Fprintf(os.Stderr, "wc: unrecognized option '%s'\n", invalidOption)
		}
	}
	// If we weren't able to figure out what the invalid option then print the whole error.
	// Hopefully we can modify the program to parse it correctly.
	if invalidOption == "" {
		fmt.Fprintf(os.Stderr, "wc: %v\n", err)
	}
	// End with a help message.
	fmt.Fprintf(os.Stderr, "Try 'wc --help' for more information.\n")
	return fmt.Errorf("invalid option")
}
