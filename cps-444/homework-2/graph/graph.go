package main

import "fmt"

// This constant determines the size of the graph, i.e. the number of vertices.
// The graph is initialized with an adjacency matrix containing this many vertices,
// identified by their index in the array.
const size = 10

type Graph struct {
	matrix [size][size]bool
}

// AddEdge adds a directed edge from "from" to "to". This is a DIGRAPH.
// "from" and "to" must be values from 0-(size-1).
func AddEdge(g *Graph, from, to int) bool {
	if from >= size || to >= size {
		fmt.Printf("AddEdge: error: graph only has %d vertices\n", size)
		return false
	}

	if from < 0 || to < 0 {
		fmt.Println("AddEdge: error: vertices must have indexes of at least 0")
		return false
	}

	g.matrix[from][to] = true
	return true
}

// HasEdge checks if there is a directed edge from "from" to "to".
func HasEdge(g *Graph, from, to int) bool {
	if from >= size || to >= size {
		fmt.Printf("HasEdge: error: graph only has %d vertices\n", size)
		return false
	}

	if from < 0 || to < 0 {
		fmt.Println("HasEdge: error: vertices must have indexes of at least 0")
		return false
	}

	return g.matrix[from][to]
}
