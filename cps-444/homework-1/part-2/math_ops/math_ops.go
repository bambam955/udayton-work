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
	fmt.Println("Sum\t\t= " + strconv.Itoa(num1+num2))
	fmt.Println("Difference\t= " + strconv.Itoa(num1-num2))
	fmt.Println("Product\t\t= " + strconv.Itoa(num1*num2))
	fmt.Println("Average\t\t= " + strconv.FormatFloat(float64(num1+num2)/2, 'f', 2, 64))
	fmt.Println("Distance\t= " + strconv.Itoa(int(math.Abs(float64(num1-num2)))))
	fmt.Println("Maximum\t\t= " + strconv.Itoa(max(num1, num2)))
	fmt.Println("Minimum\t\t= " + strconv.Itoa(min(num1, num2)))
}
