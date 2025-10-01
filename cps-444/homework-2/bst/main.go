package main

import "fmt"

func main() {
	// Add elements to the tree.
	// Reassign the pointer each time in case it was updated.
	var tree *BST
	tree = Insert(tree, 4)
	tree = Insert(tree, 14)
	tree = Insert(tree, 2)
	tree = Insert(tree, 98)
	tree = Insert(tree, 18)
	tree = Insert(tree, 267)
	tree = Insert(tree, 0)
	tree = Insert(tree, -190)
	tree = Insert(tree, 144)

	// Verify that items are properly found.
	fmt.Println(Find(tree, 267)) // SUCCESS
	fmt.Println(Find(tree, 765)) // FAIL
	fmt.Println(Find(tree, 2))   // SUCCESS
	fmt.Println(Find(tree, 78))  // FAIL

	// Output should be: [-190 0 2 4 14 18 98 144 267]
	fmt.Println(InOrder(tree))
}
