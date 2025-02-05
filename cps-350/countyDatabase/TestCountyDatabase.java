package countyDatabase;

public class TestCountyDatabase {
    public static void main(String[] args) {
        // Insert 5 counties into an empty BST.
        System.out.println("Inserting five counties...\n");
        BST tree = new BST();
        tree.insert(new County("Franklin", "049", "Columbus", 1_264_518, 539.87));
        tree.insert(new County("Hamilton", "061", "Cincinnati", 802_374, 407.36));
        tree.insert(new County("Butler", "017", "Hamilton", 368_130, 467.27));
        tree.insert(new County("Montgomery", "113", "Dayton", 535_153, 461.68));
        tree.insert(new County("Clinton", "027", "Wilmington", 42_040, 410.88));

        // Print the current contents of the tree.
        printTree(tree);

        // Insert one more county.
        System.out.println("Inserting one more county...\n");
        tree.insert(new County("Cuyahoga", "035", "Cleveland", 1_249_352, 458.49));

        // Cuyahoga will be after Clinton and before Hamilton in pre-order. This is because it's inserted as the right child of Clinton, so it's processed AFTER Clinton.
        // It will be after Clinton and before Frankling for in-order. This is because it's the right child of Clinton, but still in the left tree of the root Franklin.
        printTree(tree);

        // Delete a county from the tree.
        System.out.println("Deleting Franklin county...\n");
        tree.delete(49);

        // We know it worked because Franklin is gone, and the in-order traversal is in increasing order.
        // This worked because Franklin is the root node, so we looked down the left subtree for the largest node
        // in it and found Cuyahoga, all the way to the right side of the left subtree, and moved it to the root.
        printTree(tree);
    }

    // Print out the contents of a BST in pre-order and in-order.
    static void printTree(BST tree) {
        System.out.println("Printing pre-order...");
        tree.preorderPrint();
        System.out.println();
        System.out.println("Printing in-order...");
        tree.inorderPrint();
        System.out.println();
    }
}
