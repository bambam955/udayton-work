// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 99.

// Graph shows how to use a map of maps to represent a directed graph.
package main

import "fmt"

// !+
// var graph = make(map[string]map[string]bool)

// func addEdge(from, to string) {
// 	edges := graph[from]
// 	if edges == nil {
// 		edges = make(map[string]bool)
// 		graph[from] = edges
// 	}
// 	edges[to] = true
// }

// func hasEdge(from, to string) bool {
// 	return graph[from][to]
// }

//!-

func main() {
	var graph Graph
	graph.AddEdge(0, 1)
	graph.AddEdge(2, 3)
	graph.AddEdge(0, 3)
	graph.AddEdge(3, 0)
	fmt.Println(graph.HasEdge(0, 1))
	fmt.Println(graph.HasEdge(2, 3))
	fmt.Println(graph.HasEdge(0, 3))
	fmt.Println(graph.HasEdge(3, 0))
	fmt.Println(graph.HasEdge(20, 1))
	fmt.Println(graph.HasEdge(2, 3))
	fmt.Println(graph.HasEdge(20, 3))
	fmt.Println(graph.HasEdge(3, 20))

	// addEdge("a", "b")
	// addEdge("c", "d")
	// addEdge("a", "d")
	// addEdge("d", "a")
	// fmt.Println(hasEdge("a", "b"))
	// fmt.Println(hasEdge("c", "d"))
	// fmt.Println(hasEdge("a", "d"))
	// fmt.Println(hasEdge("d", "a"))
	// fmt.Println(hasEdge("x", "b"))
	// fmt.Println(hasEdge("c", "d"))
	// fmt.Println(hasEdge("x", "d"))
	// fmt.Println(hasEdge("d", "x"))

}
