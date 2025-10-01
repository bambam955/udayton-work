package main

import "fmt"

// This program tests the implementation of the digraph.

func main() {
	var graph Graph
	// Add a few edges between existing vertices.
	AddEdge(&graph, 0, 1)
	AddEdge(&graph, 2, 3)
	AddEdge(&graph, 0, 3)
	AddEdge(&graph, 3, 8)

	// Check for the existence of edges.
	fmt.Println(HasEdge(&graph, 0, 1))
	fmt.Println(HasEdge(&graph, 2, 3))
	fmt.Println(HasEdge(&graph, 0, 3))
	fmt.Println(HasEdge(&graph, 3, 0))  // FAIL: edge goes from 0 to 3, not 3 to 0
	fmt.Println(HasEdge(&graph, 20, 1)) // FAIL: only 10 vertices (unless size is changed)
	fmt.Println(HasEdge(&graph, 3, 2))
	fmt.Println(HasEdge(&graph, 20, 3))
	fmt.Println(HasEdge(&graph, 3, 20))
}
