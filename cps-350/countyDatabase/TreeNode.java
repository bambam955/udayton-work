package countyDatabase;

public class TreeNode {
    County county; // reference the information about the county
    TreeNode left; // reference to left child
    TreeNode right; // reference to right child

    public TreeNode(final County _county) {
        county = _county;
        left = right = null;
    }
}
