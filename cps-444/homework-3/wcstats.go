package main

import (
	"fmt"
	"os"
	"strings"
	"unicode"
)

// This is the main function.
func OutputFileStats(files []string, flags WcStatFlags) error {
	// This slice will contain all of the stats, so that they can be outputted at the end.
	var allStats []wcStats
	// These will be the aggregate stats.
	var totalStats wcStats

	// Iterate through each of the files and count up all the newlines, words, and bytes in each one.
	for _, file := range files {
		contents, err := os.ReadFile(file)
		if err != nil {
			return err
		}

		// Count the stats and append to the slice.
		stats := countStatsForText(string(contents))
		allStats = append(allStats, stats)
		// Add to the aggregate total.
		totalStats.add(stats)
		// Update the table cell size if necessary.
		// Note that we can't output anything until we go through all of the files
		// because we don't know in advance what the table cell size will be.
		tableCellFmtLen = max(tableCellFmtLen, stats.determineFmtSize(flags))
	}

	// Print out the stats for each file.
	for i, stats := range allStats {
		fmt.Printf("%s %s\n", stats.toString(flags), files[i])
	}

	// Print out the total stats if there was more than one file.
	// If there is only one file then printing "totals" would be redundant.
	if len(allStats) > 1 {
		fmt.Printf("%s total\n", totalStats.toString(flags))
	}
	return nil
}

// Track all of the stats for a file.
type wcStats struct {
	newlines int
	words    int
	bytes    int
}

// This filewide global is used to have a consistent "cell size" for each value
// in the table produced when the stats are displayed.
var tableCellFmtLen int

// This function converts a file's stats to a string according to
// the command options and cell size.
func (w *wcStats) toString(flags WcStatFlags) string {
	outputStr := ""
	if flags.showNewlines {
		outputStr += fmt.Sprintf("%*d ", tableCellFmtLen, w.newlines)
	}
	if flags.showWords {
		outputStr += fmt.Sprintf("%*d ", tableCellFmtLen, w.words)
	}
	if flags.showBytes {
		outputStr += fmt.Sprintf("%*d ", tableCellFmtLen, w.bytes)
	}

	// Trim off any extra whitespace on the end.
	return strings.TrimRightFunc(outputStr, unicode.IsSpace)
}

// Figure out the string length of each value in the stats for a file and determine
// if any of the stats are large enough as a string to increase the table cell size.
func (w *wcStats) determineFmtSize(flags WcStatFlags) int {
	newlinesFmtLen := len(fmt.Sprintf("%d", w.newlines))
	wordsFmtLen := len(fmt.Sprintf("%d", w.words))
	bytesFmtLen := len(fmt.Sprintf("%d", w.bytes))

	maxCharLen := 3
	if flags.showNewlines {
		maxCharLen = max(maxCharLen, newlinesFmtLen)
	}
	if flags.showWords {
		maxCharLen = max(maxCharLen, wordsFmtLen)
	}
	if flags.showBytes {
		maxCharLen = max(maxCharLen, bytesFmtLen)
	}

	return maxCharLen
}

// Add the stats from one file to the stats from this one.
func (w *wcStats) add(other wcStats) {
	w.newlines += other.newlines
	w.words += other.words
	w.bytes += other.bytes
}

// Count up all of the bytes, words, and newlines from an input string.
func countStatsForText(input string) wcStats {
	var stats wcStats
	stats.newlines = strings.Count(input, "\n")
	stats.bytes = len(input)
	stats.words = len(strings.Fields(input))
	return stats
}
