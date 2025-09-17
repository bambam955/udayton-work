package main

// Corresponds to part 1 problem 5.

import (
	"fmt"
	"os"
)

// This is the left half of the ASCII drawing.
var leftSideStrings = []string{
	`           oOo`,
	`   \\      O  `,
	`   (o>     O  `,
	`\\_//)     O  `,
	` \_/_)   <o   `,
	`  _|_      Ooo`,
}

// This is the right half of the ASCII drawing.
var rightSideStrings = []string{
	`oOo`,
	`  O`,
	`  O`,
	`  O`,
	`  O`,
	`OoO`,
}

const helpMsg string = `Usage: animal_greeting.go NAME`

func main() {
	// Make sure a name arg was passed
	if len(os.Args) < 2 {
		fmt.Println(helpMsg)
		return
	}

	fmt.Println()
	printGreeting(os.Args[1])
	fmt.Println()
}

func printGreeting(name string) {
	const greeting = "Hi there"
	// Figure out if the name is longer than the greeting
	size := max(len(greeting), len(name)+1) // Add 1 for exclamation point

	strs := leftSideStrings
	// Append the greeting and name to the proper places in the string array
	strs[2] += greeting
	strs[3] += (name + "!")

	// For each character in the greeting, append border characters
	// and spaces where needed
	for i := range size {
		// Use alternating "O" and "o" for the border
		nextBorderChar := "o"
		if i%2 == 0 {
			nextBorderChar = "O"
		}
		strs[0] += nextBorderChar
		strs[len(strs)-1] += nextBorderChar
		// These are the filler lines in between the border and greeting
		strs[1] += " "
		strs[4] += " "
	}
	// Fill spaces in the greeting lines if needed to make sure they're all the same length
	for len(strs[2]) < len(strs[1]) {
		strs[2] += " "
	}
	for len(strs[3]) < len(strs[1]) {
		strs[3] += " "
	}

	// Print the greeting!
	for i := range len(strs) {
		fmt.Println(strs[i] + rightSideStrings[i])
	}
}
