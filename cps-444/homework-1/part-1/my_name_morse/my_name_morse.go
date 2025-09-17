package main

// Corresponds to part 1 problem 4.

import (
	"github.com/common-nighthawk/go-figure"
)

func main() {
	// Print my name in morse code.
	myFigure := figure.NewFigure("BENNETT", "morse", true)
	myFigure.Print()
}
