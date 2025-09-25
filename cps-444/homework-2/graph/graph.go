package main

import "fmt"

type Graph struct {
	matrix [10][10]bool
}

// AddEdge adds a directed edge from `from` to `to`.
func (g *Graph) AddEdge(from, to int) bool {
	if from >= 10 || to >= 10 {
		fmt.Println("Error: graph only has 10 vertices")
		return false
	}

	if from < 0 || to < 0 {
		fmt.Println("Error: vertices must have indexes of at least 0")
		return false
	}

	g.matrix[from][to] = true
	return true
}

// HasEdge checks if there is a directed edge from `from` to `to`.
func (g *Graph) HasEdge(from, to int) bool {
	if from >= 10 || to >= 10 {
		fmt.Println("Error: graph only has 10 vertices")
		return false
	}

	if from < 0 || to < 0 {
		fmt.Println("Error: vertices must have indexes of at least 0")
		return false
	}

	return g.matrix[from][to]
}
