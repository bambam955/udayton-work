// Corresponds to part 2 problem 3.

package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
)

const helpMsg string = `USAGE: radius_calcs.go RADIUS`

func main() {
	// Verify args number.
	if len(os.Args) < 2 {
		fmt.Println(helpMsg)
		return
	}

	radius, err := strconv.ParseFloat(os.Args[1], 64)
	if err != nil {
		fmt.Fprintf(os.Stderr, "Error parsing radius from %s.\n", os.Args[1])
		os.Exit(1)
	}

	PrintCircleInfo(radius)
	PrintSphereInfo(radius)
}

func PrintCircleInfo(radius float64) {
	area := math.Pi * math.Pow(radius, 2)
	circumference := 2 * math.Pi * radius
	fmt.Printf("Circle area\t= %.2f\n", area)
	fmt.Printf("Circle circum.\t= %.2f\n", circumference)
}

func PrintSphereInfo(radius float64) {
	sphereVol := (4 / 3) * math.Pi * math.Pow(radius, 3)
	sphereSurfaceArea := 4 * math.Pi * math.Pow(radius, 2)
	fmt.Printf("Sphere volume\t= %.2f\n", sphereVol)
	fmt.Printf("Sphere SA\t= %.2f\n", sphereSurfaceArea)
}
