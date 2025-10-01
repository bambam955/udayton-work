package main

type BST struct {
	value       int  // The value of this node
	left, right *BST // Pointers to the left and right trees
}

// Insert a new value into the given tree.
func Insert(tree *BST, value int) *BST {
	// If the tree is empty then create a new one and set its value.
	if tree == nil {
		tree = new(BST)
		tree.value = value
		return tree
	}

	// Otherwise, put the value on the proper side of the tree.
	// If less than the value of the current node, it goes on the left;
	// otherwise, it goes on the right.
	if value < tree.value {
		tree.left = Insert(tree.left, value)
	} else {
		tree.right = Insert(tree.right, value)
	}

	return tree
}

// Determine whether the given value is in the given tree.
func Find(tree *BST, value int) bool {
	// If the tree is empty then the value is obviously not there.
	if IsEmpty(tree) {
		return false
	}

	// If the tree's node equals the value then we are done. It has been found.
	// Otherwise, search the proper half of the rest of the tree.
	// Since this is a BST, lesser values are on the left and higher values are on the right.
	if tree.value == value {
		return true
	} else if value < tree.value {
		return Find(tree.left, value)
	} else {
		return Find(tree.right, value)
	}
}

// Determine whether the given tree is empty or not.
func IsEmpty(tree *BST) bool {
	return tree == nil
}

// Traverse the tree in-order and return the slice of all elements.
func InOrder(tree *BST) []int {
	if IsEmpty(tree) {
		return make([]int, 0)
	}

	// Start the recursive helper off with the root of the tree.
	return inOrderHelper(tree, make([]int, 0))
}

// This function recurses until it reaches an empty tree.
func inOrderHelper(tree *BST, values []int) []int {
	if !IsEmpty(tree) {
		// Append all the values from the left side.
		values = inOrderHelper(tree.left, values)
		// Append the middle value.
		values = append(values, tree.value)
		// Append all the values from the right side.
		values = inOrderHelper(tree.right, values)
	}
	return values
}
