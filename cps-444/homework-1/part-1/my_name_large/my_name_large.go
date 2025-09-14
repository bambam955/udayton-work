package main

// Corresponds to part 1 problem 3.

import (
	"fmt"
	"os"

	"github.com/common-nighthawk/go-figure"
)

const helpMsg string = `Usage: my_name_large.go FONT_NAME

Try "basic", "cosmic", or "drpepper" to get started.

List of fonts here: https://github.com/common-nighthawk/go-figure?tab=readme-ov-file#supported-fonts`

func main() {
	// Make sure a font was passed.
	if len(os.Args) < 2 {
		fmt.Println(helpMsg)
		return
	}

	// Print my name in the specified font.
	myFigure := figure.NewFigure("BENNETT", os.Args[1], true)
	myFigure.Print()
}
