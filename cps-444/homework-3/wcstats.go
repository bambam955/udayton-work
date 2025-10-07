package main

import (
	"fmt"
	"os"
	"strings"
	"unicode"
)

// Track all of the stats for a file.
type wcStats struct {
	newlines int
	words    int
	bytes    int
}

var tableCellFmtLen int

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

	return strings.TrimRightFunc(outputStr, unicode.IsSpace)
}

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

func (w *wcStats) add(other wcStats) {
	w.newlines += other.newlines
	w.words += other.words
	w.bytes += other.bytes
}

func OutputStats(files []string, flags WcStatFlags) error {
	var allStats []wcStats
	var totalStats wcStats
	for _, file := range files {
		contents, err := os.ReadFile(file)
		if err != nil {
			return err
		}

		stats := countStatsForText(string(contents))
		allStats = append(allStats, stats)
		totalStats.add(stats)
		tableCellFmtLen = max(tableCellFmtLen, stats.determineFmtSize(flags))
	}

	for i, stats := range allStats {
		fmt.Printf("%s %s\n", stats.toString(flags), files[i])
	}
	fmt.Printf("%s total\n", totalStats.toString(flags))
	return nil
}

func countStatsForText(input string) wcStats {
	var stats wcStats
	stats.newlines = strings.Count(input, "\n")
	stats.bytes = len(input)
	stats.words = len(strings.Fields(input))
	return stats
}
