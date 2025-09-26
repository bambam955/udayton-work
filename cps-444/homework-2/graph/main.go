package main

import "fmt"

func main() {
	var graph Graph
	AddEdge(&graph, 0, 1)
	AddEdge(&graph, 2, 3)
	AddEdge(&graph, 0, 3)
	AddEdge(&graph, 3, 0)
	fmt.Println(HasEdge(&graph, 0, 1))
	fmt.Println(HasEdge(&graph, 2, 3))
	fmt.Println(HasEdge(&graph, 0, 3))
	fmt.Println(HasEdge(&graph, 3, 0))
	fmt.Println(HasEdge(&graph, 20, 1))
	fmt.Println(HasEdge(&graph, 2, 3))
	fmt.Println(HasEdge(&graph, 20, 3))
	fmt.Println(HasEdge(&graph, 3, 20))
}
