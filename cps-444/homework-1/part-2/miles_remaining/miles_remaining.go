// Corresponds to part 2 problem 5.

package main

import (
	"fmt"
	"os"
	"strconv"
)

const helpMsg string = `USAGE: miles_remaining.go GAS_IN_TANK FUEL_EFF GAS_PRICE

This program helps you figure out how much you are paying for gas and
how far you can go with the gas currently in your tank.

GAS_IN_TANK = the amount of gas (gallons) in the tank
FUEL_EFF = your car's fuel efficiency (MPG)
GAS_PRICE = the current price for a gallon of gas`

func main() {
	// Verify arguments.
	if len(os.Args) != 4 {
		fmt.Println(helpMsg)
		return
	}

	// Parse numbers from the arguments.
	var values [3]float64
	for i := range len(values) {
		temp, err := strconv.ParseFloat(os.Args[i+1], 64)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error: could not parse float: %s\n", os.Args[i+1])
			os.Exit(1)
		}
		values[i] = temp
	}

	// Calculate outputs.
	costPer100Miles := 100.0 / values[1] * values[2]
	howFarYouCanGo := values[0] * values[1]

	// Print results.
	fmt.Printf("Cost per 100 miles\t= %.2f\n", costPer100Miles)
	fmt.Printf("Distance remaining\t= %.2f\n", howFarYouCanGo)
}
