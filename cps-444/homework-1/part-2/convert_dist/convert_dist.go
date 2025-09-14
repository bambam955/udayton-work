// Corresponds to part 2 problem 2.

package main

import (
	"fmt"
	"os"
	"strconv"
)

// Got the conversion rate from Google
const metersToMiles = 0.000621371192

const helpMsg string = `USAGE: convert_dist.go METERS`

func main() {
	// Make sure the user passed a distance argument.
	if len(os.Args) < 2 {
		fmt.Println(helpMsg)
		return
	}

	// Convert the arg to meters.
	meters, err := strconv.ParseFloat(os.Args[1], 64)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error parsing float from %s.\n", os.Args[1])
		os.Exit(1)
	}

	// Print results.
	fmt.Println("DISTANCE CONVERSIONS")
	fmt.Printf("Meters\t= %.2f\n", meters)
	miles := meters * metersToMiles
	fmt.Printf("Miles\t= %.2f\n", miles)
	fmt.Printf("Feet\t= %.2f\n", miles*5280)
	fmt.Printf("Inches\t= %.2f\n", +miles*5280*12)
}
