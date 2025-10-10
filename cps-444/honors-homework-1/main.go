package main

import (
	"fmt"
	"os"
)

// This program tests the various pieces of the digraph implementation,
// including construction, pathfinding, and cycle detection.

func main() {
	// We should have been passed a file name as the only argument. Verify this is the case.
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s GRAPH_FILE", os.Args[0])
		os.Exit(1)
	}

	// Create the graph from the file. Exit immediately if there is an error.
	graph, err := CreateGraphFromFile(os.Args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v", err)
		os.Exit(1)
	}

	// Output the created graph structure.
	graph.DumpGraph()

	// Ask the user for input on what node to trace distances from.
	var inputNode string
	fmt.Printf("start node? ")
	fmt.Scanf("%s", &inputNode)
	// Calculate the shortest distance from the inputted node to all other nodes in the graph.
	for _, n := range graph.Nodes() {
		dist, err := graph.MinDistance(inputNode, n.Id)
		if err != nil {
			fmt.Println(err.Error())
			break
		}
		fmt.Printf("shortest distance from %s to %s: %d\n", inputNode, n.Id, dist)
	}

	// Check to see whether the graph has a cycle.
	if graph.HasCycle() {
		fmt.Println("The graph has a cycle.")
	} else {
		fmt.Println("The graph does not have a cycle.")
	}
}
