package main

import (
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

// This type represents a node in the graph.
type GraphNode struct {
	// The name of the node. These will be unique.
	Id string
	// The edges from this node to other nodes.
	// The mapping is from the other nodes to the weight of the edge between them.
	edges map[*GraphNode]int
}

// This type represents a directed graph.
// Nodes and the edges between them can be added via the AddEdge function.
type Graph struct {
	nodes []*GraphNode
}

// This method provides read-only access to the graph's nodes.
func (g *Graph) Nodes() []*GraphNode {
	copiedNodes := make([]*GraphNode, len(g.nodes))
	// NOTE: I had to Google how to do this. There might be
	// a more performant solution but this works.
	copy(copiedNodes, g.nodes)
	return copiedNodes
}

// This function creates a graph from the file at the given filename.
// The file must be in a specific format where each line represents an edge,
// structured as "<sourceNode> <destNode> <weight>".
// Any errors from reading the file or parsing weights will be returned.
// If all parsing is successful then the completed graph will be returned.
func CreateGraphFromFile(filename string) (*Graph, error) {
	// Read the file.
	contents, readErr := os.ReadFile(filename)
	if readErr != nil {
		return nil, readErr
	}

	// Split into separate lines.
	entries := strings.Split(string(contents), "\n")
	var graph Graph
	for _, entry := range entries {
		// Skip empty lines.
		if len(entry) == 0 {
			continue
		}
		// Separate the line into its various parts.
		// The 3 parts should be space-separated.
		edgeParts := strings.Fields(entry)
		if len(edgeParts) == 3 {
			// Parse out the weight from the third piece. Return any errors.
			weight, err := strconv.ParseInt(edgeParts[2], 10, 32)
			if err != nil {
				return nil, err
			}

			// At this point, we have all the pieces ready for an edge!
			// Add the edge to the graph.
			graph.AddEdge(edgeParts[0], edgeParts[1], int(weight))
		} else {
			// Return an error if the line was not formatted correctly.
			err := fmt.Errorf("could not parse edge from '%s'", entry)
			return nil, err
		}
	}
	return &graph, nil
}

// The AddEdge method adds an edge to the graph between nodes with the given IDs.
// If the given IDs do not yet have nodes associated with them then they will be created;
// if both nodes already exist and there is already an edge between them then a new edge
// will NOT be created. The weight must be a positive integer.
func (g *Graph) AddEdge(from, to string, weight int) bool {
	if weight <= 0 {
		return false
	}

	// Create nodes for the given node names if they don't already exist.
	// Note that the "to" node will be created even though it doesn't have any edges
	// going out from it.
	if !g.hasNode(from) {
		g.createNode(from)
	}
	if !g.hasNode(to) {
		g.createNode(to)
	}

	// Do not create new edges if one already exist.
	if g.HasEdge(from, to) {
		fmt.Printf("AddEdge: error: node %s already has edge to node %s, weight %d", from, to, weight)
		return false
	}

	// Add the edge.
	g.findNode(from).edges[g.findNode(to)] = weight
	return true
}

// The HasEdge method checks if there is a directed edge between the nodes with
// the given IDs. If either of the nodes doesn't exist then the result will be false.
func (g *Graph) HasEdge(from, to string) bool {
	for _, node := range g.nodes {
		if node.Id == from {
			_, exists := node.edges[g.findNode(to)]
			return exists
		}
	}

	return false
}

// Create a new node. Basically just a convenience function for initialization.
// If a node with the given ID already exists then a new one will not be created.
func (g *Graph) createNode(id string) {
	if g.hasNode(id) {
		return
	}

	var newNode GraphNode
	newNode.Id = id
	newNode.edges = make(map[*GraphNode]int)
	g.nodes = append(g.nodes, &newNode)
}

// Determine whether the graph has a node with the given ID.
func (g *Graph) hasNode(id string) bool {
	return g.findNode(id) != nil
}

// Convenience function for iterating over a graph's nodes to find
// the node with the given ID. This is a very common operation.
func (g *Graph) findNode(id string) *GraphNode {
	for _, node := range g.nodes {
		if node.Id == id {
			return node
		}
	}

	return nil
}

// The MinDistance method uses Dijkstra's algorithm to determine the minimum distance
// between the given two nodes. It takes into account the weights of all edges.
// If either of the given nodes does not exist then an error will be returned.
// If there is no path from the source to the destination then the result will be -1.
func (g *Graph) MinDistance(from, to string) (int, error) {
	if !g.hasNode(from) {
		err := fmt.Errorf("starting node %s not found", from)
		return 0, err
	}
	if !g.hasNode(to) {
		err := fmt.Errorf("destination node %s not found", to)
		return 0, err
	}

	// NOTE: I Googled "pseudocode for Dijkstra's algorithm" to help me out with this,
	// but I did not search for a Go-specific implementation.

	// Map of each node to its current determined distance from the source node.
	// Distance from source to itself starts at 0, all others start at infinity (largest int).
	dists := make(map[*GraphNode]int)
	for _, n := range g.nodes {
		dists[n] = math.MaxInt
	}
	dists[g.findNode(from)] = 0
	// This tracks which nodes have been visited by the algorithm.
	// All nodes accessible from the source node will be visited exactly once.
	visited := make(map[*GraphNode]bool)
	// This will be a map of node ID to its previously traced node.
	// These can be used to build a path from the source to the destination if desired.
	preds := make(map[*GraphNode]*GraphNode)

	for range g.nodes {
		// Determine the closest UNVISITED node in the graph.
		// To start this will be the source node itself.
		// After that, the next closest node will be found. This ensures that we
		// determine all paths from shortest to longest.
		var closestUnvisited *GraphNode = nil
		minDist := math.MaxInt
		for _, v := range g.nodes {
			if !visited[v] && dists[v] < minDist {
				minDist = dists[v]
				closestUnvisited = v
			}
		}

		// There are no more nodes to visit. Exit the loop.
		// This can happen if the graph is not fully connected, i.e. not all nodes
		// have a path from the given source node.
		if closestUnvisited == nil {
			break
		}

		// Mark the node as visited. We don't want to come back to it again.
		// Without this, we'd just stay on the source node the whole time because
		// it will always be "closest" to the source.
		visited[closestUnvisited] = true

		// Go through each edge stemming from the current focused node.
		// If the neighbor has already been visited then we know that its shortest path
		// is already determined. How? Because for a node to have been visited already,
		// it must have been CLOSER TO THE SOURCE than the current node.
		// However, if the neighbor hasn't been visited yet, then that means the current node
		// is by definition closer to the source than it, so it's possible that the shortest path to
		// that node goes through this one. We check if this is the case, and if it is,
		// then set the previously traced node for the neighbor to the current node and the
		// shortest distance to that node to the newly calculated distance.
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

	// It's possible that some nodes were never visited if they aren't accessible from
	// the source node. Set their distances to -1. This is an acceptable "null" value
	// because we only allow positive weights.
	for n := range dists {
		if !visited[n] {
			dists[n] = -1
		}
	}
	return dists[g.findNode(to)], nil
}

// The next two functions are used to figure out whether the graph contains a cycle.
// The basic idea is to run a DFS from each node to try to find cycles.
func (g *Graph) HasCycle() bool {
	visitedNodes := make(map[*GraphNode]bool, len(g.nodes))
	// Run a DFS on each node.
	for _, node := range g.nodes {
		// This allows the recursive operation to track all the nodes it's visited in the current DFS.
		currentNodePath := make(map[*GraphNode]bool, len(g.nodes))
		// If a cycle is found then return immediately. No need to go further.
		if g.findCyclesWithNode(node, visitedNodes, currentNodePath) {
			return true
		}
	}

	// If we get to here then no cycles were found in any subgraphs.
	return false
}
func (g *Graph) findCyclesWithNode(n *GraphNode, visited, currentPath map[*GraphNode]bool) bool {
	visited[n] = true
	// Add this node to the current path.
	// This "path" is like the metaphorical ball of string being unwound, except we don't track order.
	// We just know that there is a path through all the nodes.
	currentPath[n] = true

	for neighbor := range n.edges {
		// Avoid running a DFS from a node that's already been fully explored.
		// If we are still exploring then there must've been no cycle in that subgraph so there's
		// no need to explore it again.
		// However, if the node has been visited before, AND it's in the current path, then
		// that means there must be a cycle, because we have traced a path from the current node
		// through other nodes all the way back to the current one. Return immediately.
		if !visited[neighbor] {
			if g.findCyclesWithNode(neighbor, visited, currentPath) {
				return true
			}
		} else if currentPath[neighbor] {
			return true
		}
	}

	// If we get here then no cycle was found. Take this node out of the current path.
	// This represents "backtracking" in the DFS, up a level closer to the starting point,
	// so that we can go down another path to try again.
	currentPath[n] = false
	return false
}

// Print the structure of the graph to stdout. This is useful for debugging purposes.
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
