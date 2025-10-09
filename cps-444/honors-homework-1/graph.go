package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type GraphNode struct {
	Id    string
	edges map[*GraphNode]int
}

type Graph struct {
	nodes []*GraphNode
}

func (g *Graph) Nodes() []*GraphNode {
	copiedNodes := make([]*GraphNode, len(g.nodes))
	copy(copiedNodes, g.nodes)
	return copiedNodes
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

	if g.HasEdge(from, to) {
		fmt.Printf("AddEdge: error: node %s already has edge to node %s, weight %d", from, to, weight)
		return false
	}

	g.findNode(from).edges[g.findNode(to)] = weight
	return true
}

// HasEdge checks if there is a directed edge from "from" to "to".
func (g *Graph) HasEdge(from, to string) bool {
	for _, node := range g.nodes {
		if node.Id == from {
			_, exists := node.edges[g.findNode(to)]
			return exists
		}
	}

	return false
}

func (g *Graph) createNode(id string) *GraphNode {
	n := g.findNode(id)
	if n != nil {
		return n
	}

	var newNode GraphNode
	newNode.Id = id
	newNode.edges = make(map[*GraphNode]int)
	g.nodes = append(g.nodes, &newNode)
	return &newNode
}

func (g *Graph) findNode(id string) *GraphNode {
	for _, node := range g.nodes {
		if node.Id == id {
			return node
		}
	}

	return nil
}

func (g *Graph) hasNode(id string) bool {
	return g.findNode(id) != nil
}

func (g *Graph) MinDistance(from, to string) (int, error) {
	if !g.hasNode(from) {
		err := fmt.Errorf("starting node %s not found", from)
		return 0, err
	}
	if !g.hasNode(to) {
		err := fmt.Errorf("destination node %s not found", to)
		return 0, err
	}

	// This will be a map of node to current distance
	dists := make(map[*GraphNode]int)
	for _, n := range g.nodes {
		dists[n] = math.MaxInt
	}
	dists[g.findNode(from)] = 0
	// Nodes for which shortest path is finalized
	visited := make(map[*GraphNode]bool)
	// This will be a map of node ID to its previously traced node
	preds := make(map[*GraphNode]*GraphNode)
	// Queue of nodes
	nodes := g.nodes

	for range nodes {
		var closestUnvisited *GraphNode = nil
		minDist := math.MaxInt
		for _, v := range nodes {
			if !visited[v] && dists[v] < minDist {
				minDist = dists[v]
				closestUnvisited = v
			}
		}

		if closestUnvisited == nil {
			break
		}

		visited[closestUnvisited] = true

		for neighbor, weight := range closestUnvisited.edges {
			if !visited[neighbor] {
				altDist := dists[closestUnvisited] + weight
				if altDist < dists[neighbor] {
					dists[neighbor] = altDist
					preds[neighbor] = closestUnvisited
				}
			}
		}
	}

	return dists[g.findNode(to)], nil
}

func (g *Graph) HasCycle() bool {
	visitedNodes := make(map[*GraphNode]bool, len(g.nodes))
	for _, node := range g.nodes {
		currentNodes := make(map[*GraphNode]bool, len(g.nodes))
		if g.findCyclesWithNode(node, visitedNodes, currentNodes) {
			return true
		}
	}

	return false
}

func (g *Graph) findCyclesWithNode(n *GraphNode, visited, current map[*GraphNode]bool) bool {
	visited[n] = true
	current[n] = true
	for neighbor := range n.edges {
		if !visited[neighbor] {
			if g.findCyclesWithNode(neighbor, visited, current) {
				return true
			}
		} else if current[neighbor] {
			return true
		}
	}

	current[n] = false
	return false
}

func (g *Graph) DumpGraph() {
	for _, node := range g.nodes {
		if len(node.edges) == 0 {
			continue
		}
		var edgesStr string
		for edge, weight := range node.edges {
			edgesStr = fmt.Sprintf("%s %s[%d]", edgesStr, edge.Id, weight)
		}
		fmt.Printf("%s: [%s ]\n", node.Id, edgesStr)
	}
}
