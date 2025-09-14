// Corresponds to part 2 problem 1.

package main

import (
	"fmt"
	"os"
)

const helpMsg string = `USAGE: math_ops.go NUM1 NUM2`

func main() {
	// We need exactly 2 numbers. No other amounts are supported.
	if len(os.Args) != 3 {
		fmt.Println(helpMsg)
		return
	}
}
