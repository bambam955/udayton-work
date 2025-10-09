package main

import "fmt"

// This program tests the implementation of the digraph.

func main() {
	var graph Graph
	// Add a few edges between existing vertices.
	graph.AddEdge("0", "1")
	graph.AddEdge("2", "3")
	graph.AddEdge("0", "3")
	graph.AddEdge("3", "8")

	// Check for the existence of edges.
	fmt.Println(graph.HasEdge("0", "1"))
	fmt.Println(graph.HasEdge("2", "3"))
	fmt.Println(graph.HasEdge("0", "3"))
	fmt.Println(graph.HasEdge("3", "0")) // FAIL: edge goes from "0" to "3", not "3" to "0"
	fmt.Println(graph.HasEdge("20", "1"))
	fmt.Println(graph.HasEdge("3", "2"))
	fmt.Println(graph.HasEdge("20", "3"))
	fmt.Println(graph.HasEdge("3", "20"))
}
