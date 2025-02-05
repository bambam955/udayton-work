package countyDatabase;

public class BST {
    private TreeNode root;

    // No-arg constructor
    public BST() {
        root = null;
    }

    // Insert an element into the tree. Uses recursion.
    public void insert(County value) {
        root = insertRec(root, value);
    }
    private static TreeNode insertRec(TreeNode r, County value) {
        // We've found the spot to insert. Return a new node with the given value.
        if (r == null)
            return new TreeNode(value);
        
        // Do not insert the value if it's already in the tree.
        if (r.county.fips == value.fips)
            return r;
        
        // Traverse to the left or right, looking for an empty spot for a new leaf.
        if (value.fips < r.county.fips)
            r.left = insertRec(r.left, value);
        else
            r.right = insertRec(r.right, value);

        return r;
    }

    // Delete an element from the tree. Uses recursion.
    public void delete(int value) {
        deleteRec(root, value);
    }
    private static TreeNode deleteRec(TreeNode root, int value) {
        // Value is not in the tree. Can't delete anything.
        if (root == null)
            return null;

        // Traverse to the left or right to continue searching for the given FIPS code.
        if (value < root.county.fips) {
            root.left = deleteRec(root.left, value);
            return root;
        }
        else if (value > root.county.fips) {
            root.right = deleteRec(root.right, value);
            return root;
        }
        // We found the value...now we need to delete it without losing its children.
        else {
            // If one leaf is null, this is easy. Just move the other one into the deleted node's spot.
            if (root.left == null)
                return root.right;
            else if (root.right == null) {
                return root.left;
            }
            // If both leaves have values, deletion is a little more difficult.
            else {
                // If the left subtree from the root just continues left, we can scoot it up a level.
                // This will fit with the right child because whatever is left of the deleted value
                // is smaller and thus can have the same right child as the deleted value.
                if (root.left.right == null)
                {
                    root.county = root.left.county;
                    root.left = root.left.left;
                    return root;
                }
                // If all else fails, find the largest node in the left subtree and swap it with the deleted node.
                // This will be the farthest right node in the subtree.
                else {
                    root.county = findLargestAndRemove(root.left);
                    return root;
                }
            }
        }
    }
    // Find the largest child of a given tree/subtree. It will be all the way on the right.
    private static County findLargestAndRemove(TreeNode root) {
        // Continue going right till we can't go right anymore.
        if (root.right.right == null) {
            County ret = root.right.county;
            root.right = root.right.left;
            return ret;
        }
        else
            return findLargestAndRemove(root.right);
    }

    // Print in pre-order. Uses recursion.
    public void preorderPrint() {
        preorderRec(root);
    }
    private static void preorderRec(TreeNode r) {
        // Reached a leaf. Nothing more to print.
        if (r == null)
            return;

        // When traversing, this will look at the root BEFORE the children.
        r.county.print();
        preorderRec(r.left);
        preorderRec(r.right);
    }

    // Print in in-order. Uses recursion.
    public void inorderPrint() {
        inorderRec(root);
    }
    private static void inorderRec(TreeNode r) {
        // Reached a leaf. Nothing more to print.
        if (r == null)
            return;
        
        // When traversing, this will look at the root AFTER the left but BEFORE the right child.
        // This will result in going through all the elements in increasing order.
        inorderRec(r.left);
        r.county.print();
        inorderRec(r.right);
    }
}
