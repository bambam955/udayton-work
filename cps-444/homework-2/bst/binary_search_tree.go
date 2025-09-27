package main

type BST struct {
	value       int
	left, right *BST
}

func Insert(tree *BST, value int) bool {
	tree.value = value
	tree.left = tree
	tree.right = tree
	return false
}

func Find(tree *BST, value int) bool {
	return false
}

func IsEmpty(tree *BST) bool {
	return false
}

func InOrder(tree *BST) []int {
	return make([]int, 0)
}
