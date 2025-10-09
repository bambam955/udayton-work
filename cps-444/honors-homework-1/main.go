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

	var inputNode string
	fmt.Printf("start node? ")
	fmt.Scanf("%s", &inputNode)

	// node := graph.Nodes()[0]
	for _, n := range graph.Nodes() {
		dist, _ := graph.MinDistance(inputNode, n.Id)
		fmt.Printf("shortest distance from %s to %s: %d\n", inputNode, n.Id, dist)
	}

	if graph.HasCycle() {
		fmt.Println("The graph has a cycle")
	} else {
		fmt.Println("The graph does not have a cycle")
	}
}
