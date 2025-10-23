package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var philoNames []string
	fmt.Println("Enter philosopher names (^D to end): ")

	for scanner.Scan() {
		text := scanner.Text()
		philoNames = append(philoNames, strings.TrimSpace(text))
	}

	// Set the table for the philosophers to start dining
}
