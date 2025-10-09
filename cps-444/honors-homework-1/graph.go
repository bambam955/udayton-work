package main

import "fmt"

// This constant determines the size of the graph, i.e. the number of vertices.
// The graph is initialized with an adjacency matrix containing this many vertices,
// identified by their index in the array.
const size = 10

type node struct {
	id    string
	edges map[string]int
}

type Graph struct {
	nodes []node
}

// AddEdge adds a directed edge from "from" to "to". This is a DIGRAPH.
// "from" and "to" must be values from 0-(size-1).
func (g *Graph) AddEdge(from, to string) bool {
	weight := 1
	if !g.hasNode(from) {
		g.createNode(from)
	}

	if !g.hasNode(to) {
		g.createNode(to)
	}

	for _, node := range g.nodes {
		if node.id == from {
			_, exists := node.edges[to]
			if exists {
				fmt.Printf("AddEdge: error: node %s already has edge to node %s, weight %d", from, to, weight)
				return false
			} else {
				node.edges[to] = weight
				return true
			}
		}
	}

	return false
}

// HasEdge checks if there is a directed edge from "from" to "to".
func (g *Graph) HasEdge(from, to string) bool {
	for _, node := range g.nodes {
		if node.id == from {
			_, exists := node.edges[to]
			return exists
		}
	}

	return false
}

func (g *Graph) createNode(id string) {
	if g.hasNode(id) {
		return
	}

	var newNode node
	newNode.id = id
	newNode.edges = make(map[string]int)
	g.nodes = append(g.nodes, newNode)
}

func (g *Graph) hasNode(id string) bool {
	for _, node := range g.nodes {
		if node.id == id {
			return true
		}
	}

	return false
}
