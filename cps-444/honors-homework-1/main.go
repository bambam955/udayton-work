package main

import (
	"fmt"
	"os"
)

// This program tests the implementation of the digraph.

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s GRAPH_FILE", os.Args[0])
		os.Exit(1)
	}

	graph, err := CreateGraphFromFile(os.Args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "%v", err)
		os.Exit(1)
	}

	graph.DumpGraph()
}
