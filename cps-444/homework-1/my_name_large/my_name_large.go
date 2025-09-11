package main

import (
	"fmt"
	"os"

	"github.com/common-nighthawk/go-figure"
)

const helpMsg string = `Usage: my_name_large.go FONT

List of fonts here: https://github.com/common-nighthawk/go-figure?tab=readme-ov-file#supported-fonts`

// Corresponds to problem 1 part 3
func main() {
	if len(os.Args) < 2 {
		fmt.Println(helpMsg)
		return
	}
	myFigure := figure.NewFigure("BENNETT", os.Args[1], true)
  	myFigure.Print()
}
