package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

type node struct {
	id    string
	edges map[string]int
}

type Graph struct {
	nodes []node
}

func CreateGraphFromFile(filename string) (*Graph, error) {
	contents, readErr := os.ReadFile(filename)
	if readErr != nil {
		return nil, readErr
	}

	entries := strings.Split(string(contents), "\n")
	var graph Graph
	for _, entry := range entries {
		edgeParts := strings.Fields(entry)
		if len(edgeParts) == 3 {
			weight, _ := strconv.ParseInt(edgeParts[2], 10, 32)
			graph.AddEdge(edgeParts[0], edgeParts[1], int(weight))
		}
	}
	return &graph, nil
}

// AddEdge adds a directed edge from "from" to "to". This is a DIGRAPH.
// "from" and "to" must be values from 0-(size-1).
func (g *Graph) AddEdge(from, to string, weight int) bool {
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
