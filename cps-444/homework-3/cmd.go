package main

import (
	"fmt"

	"github.com/spf13/pflag"
)

var lines = pflag.BoolP("lines", "l", false, "print the newline counts")
var words = pflag.BoolP("words", "w", false, "print the word counts")
var chars = pflag.BoolP("chars", "m", false, "print the character counts")
var helpFlag = pflag.BoolP("help", "", false, "display this help and exit")

func init() {
	// Set up the help message.
	pflag.Usage = func() {
		// If we let this get printed with printDefaults() then it will be in the middle.
		// We want --help at the end.
		if f := pflag.Lookup("help"); f != nil {
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
		fmt.Println(msg)
		pflag.PrintDefaults()
		// Manually print at the end of the helpmsg.
		fmt.Println("      --help    display this help and exit")
	}
}

func Execute() {
	pflag.Parse()

	if *helpFlag {
		pflag.Usage()
		return
	}

	fmt.Printf("%t %t %t\n", *lines, *words, *chars)
}
