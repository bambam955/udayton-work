package main

import (
	"fmt"
	"os"

	"digraph"
)

// This program tests the cycle-checking piece of the digraph implementation.

func main() {
	// We should have been passed a file name as the only argument. Verify this is the case.
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s GRAPH_FILE", os.Args[0])
		os.Exit(1)
	}
	filename := os.Args[1]

	// Create the graph from the file. Exit immediately if there is an error.
	graph, err := digraph.CreateGraphFromFile(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v", err)
		os.Exit(1)
	}

	// Output the created graph structure.
	graph.DumpGraph()

	// Check to see whether the graph has a cycle.
	if graph.HasCycle() {
		fmt.Printf("%s: this graph has a cycle.\n", filename)
	} else {
		fmt.Printf("%s: this graph does not have a cycle.\n", filename)
	}
}
