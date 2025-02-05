public class BinaryMaxHeap {
    private static final int DEFAULT_CAPACITY = 10;
    private int count = 0;
    private Item[] array;
    private Item.GreedyFactor factorField;

    // Create an empty heap. Tell the algorithms what to use as the priority factor.
    public BinaryMaxHeap(final Item.GreedyFactor _factorField) {
        count = 0;
        array = new Item[DEFAULT_CAPACITY];
        factorField = _factorField;
    }

    // Insert a new item. Resize the underlying array if needed.
    public void insert(int id, double weight, double value) {
        if (count == array.length) // Resize
            resize(array.length * 2);
        array[count] = new Item(id, weight, value, factorField); // Add new item
        percolateUp(count); // Restore heap structure
        count++;
    }

    // Delete the highest-priority item from the heap (i.e. the root) and return it.
    public Item deleteMax() {
        if (count == 0) // Prevent errors for empty heap
            return null;
        Item max = array[0];
        array[0] = array[count - 1]; // Set root to lowest-priority item
        count--;
        percolateDown(0); // Restore heap structure
        return max;
    }

    // Restore the heap structure, starting from the bottom and going to the root
    private void percolateUp(int index) {
        while ((index - 1) / 2 >= 0 && // Make sure we haven't reached the root yet 
               array[index].factor() > array[(index - 1) / 2].factor()) { // Stop when parent is higher priority than given child
            swap(index, (index - 1) / 2); // If parent is lower priority, swap with child
            index = (index - 1) / 2; // Go up one level in the heap
        }
    }

    // Restore the heap structure, starting from the top and going to the last element
    private void percolateDown(int index) {
        while (2 * index + 1 <= count - 1) { // Make sure the node has at least one child
            int j = 2 * index + 1; // Index of left child
            // If node at i has two children, pick larger child:
            if (j < count - 1 && array[j + 1].factor() > array[j].factor()) // Use the given priority factor
                j++; // gets index of right child
            if (array[index].factor() > array[j].factor()) // Stop if the parent is larger than both children
                break;
            swap(index, j); // If child is higher priority, swap parent and child
            index = j; // go down one level in the heap
        }
    }

    // Swap the values at two different array indices.
    private void swap(int index1, int index2) {
        Item temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }

    // Resize the heap to the given size to make more room.
    private void resize(int newSize) {
        Item[] old = array;
        array = new Item[newSize];
        for (int i = 0; i < old.length; i++) {
            array[i] = old[i];
        }
    }
}
