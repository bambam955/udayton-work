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
	fmt.Println("Meters\t= " + strconv.FormatFloat(meters, 'f', 2, 64))
	miles := meters * metersToMiles
	fmt.Println("Miles\t= " + strconv.FormatFloat(miles, 'f', 2, 64))
	fmt.Println("Feet\t= " + strconv.FormatFloat(miles*5280, 'f', 2, 64))
	fmt.Println("Inches\t= " + strconv.FormatFloat(miles*5280*12, 'f', 2, 64))
}
