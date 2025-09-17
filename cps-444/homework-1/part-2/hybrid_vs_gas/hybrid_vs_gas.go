// Corresponds to part 2 problem 4.

package main

import (
	"fmt"
	"os"
	"strconv"
)

const helpMsg string = `USAGE: hybrid_vs_gas.go COST_NEW YEARLY_MILES GAS_PRICE MPG RESALE_VALUE

This program helps you decide whether to get a hybrid or gas car by
breaking down the costs of each option over the next 5 years.

COST_NEW = the cost of buying the car brand-new
YEARLY_MILES = the estimated miles driven per year
GAS_PRICE = the estimated gas price
MPG = car fuel efficiency (miles per gallon)
RESALE_VALUE = the estimated resale value after 5 years`

func main() {
	if len(os.Args) != 6 {
		fmt.Println(helpMsg)
		return
	}

	var values [5]float64
	for i := range len(values) {
		temp, err := strconv.ParseFloat(os.Args[i+1], 64)
		if err != nil {
			fmt.Fprintf(os.Stderr, "Error: could not parse float: %s\n", os.Args[i+1])
			os.Exit(1)
		}
		values[i] = temp
	}

	// Calculate 5-year total costs.
	// New cost minus resale cost
	depreciation := values[0] - values[4]
	// Miles per year divided by miles per gallon times gas price
	gasCostPerYear := values[1] / values[3] * values[2]
	totalGasCost := gasCostPerYear * 5
	totalCost := depreciation + totalGasCost

	// Print results.
	fmt.Printf("Gas costs (1 year)\t= %.2f\n", gasCostPerYear)
	fmt.Printf("Gas costs (5 years)\t= %.2f\n", totalGasCost)
	fmt.Printf("Depreciation (5 years)\t= %.2f\n", depreciation)
	fmt.Printf("TOTAL 5-YEAR COSTS\t= %.2f\n", totalCost)
}

/*
 * Values I used from the Web:
 *
 * HYBRID: 2026 Toyota Prius
 *   New price $28,550; MPG 56
 *   Resale value of 2021 Prius: $20,990
 *
 * GAS: 2026 Toyota Camry
 *   New price $29,000; MPG 46
 *   Resale value of 2021 Camry: $21,590
 *
 * Gas price today: $2.67/gal
 */
