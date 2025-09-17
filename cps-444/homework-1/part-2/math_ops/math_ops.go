// Corresponds to part 2 problem 1.

package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
)

const helpMsg string = `USAGE: math_ops.go INT1 INT2`

func main() {
	// We need exactly 2 numbers. No other amounts are supported.
	if len(os.Args) != 3 {
		fmt.Println(helpMsg)
		return
	}

	// Convert the program arguments to numbers.
	num1, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error parsing integer from %s.\n", os.Args[1])
		os.Exit(1)
	}
	num2, err := strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error parsing integer from %s.\n", os.Args[2])
		os.Exit(1)
	}

	// Print all of the relevant information about the numbers.
	fmt.Printf("MATH STATS for %d and %d:\n", num1, num2)
	fmt.Printf("Sum\t\t= %d\n", num1+num2)
	fmt.Printf("Difference\t= %d\n", num1-num2)
	fmt.Printf("Product\t\t= %d\n", num1*num2)
	fmt.Printf("Average\t\t= %.2f\n", float64(num1+num2)/2)
	fmt.Printf("Distance\t= %d\n", int(math.Abs(float64(num1-num2))))
	fmt.Printf("Maximum\t\t= %d\n", max(num1, num2))
	fmt.Printf("Minimum\t\t= %d\n", min(num1, num2))
}
