package main

// Corresponds to part 1 problem 2.

import (
	"flag"
	"fmt"
)

func main() {
	flag.Parse()
	if flag.NArg() != 1 {
		fmt.Println("Usage: name_box NAME")
		return
	}

	PrintWithBorder(flag.Arg(0))
}

func PrintWithBorder(name string) {
	borderlen := len(name) + 4
	// Print top line of border
	for i := range borderlen {
		switch i {
		case 0, borderlen - 1:
			fmt.Print("+")
		default:
			fmt.Print("-")
		}
	}
	fmt.Println()

	// Print middle line which includes the name
	for i := range 5 {
		switch i {
		case 0, 4:
			fmt.Print("|")
		case 1, 3:
			fmt.Print(" ")
		case 2:
			fmt.Print(name)
		}
	}
	fmt.Println()

	// Print bottom line of border
	for i := range borderlen {
		switch i {
		case 0, borderlen - 1:
			fmt.Print("+")
		default:
			fmt.Print("-")
		}
	}
	fmt.Println()
}
