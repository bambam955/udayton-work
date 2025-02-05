public class TestGreedyKnapsack {
    public static void main(String[] args) {
        // Test the algorithm for each of the priority factor options.
        for (Item.GreedyFactor factor : Item.GreedyFactor.values()) {
            greedy(factor);
        }
    }

    // Greedy algorithm that fills the imaginary knapsack based on the given priority determinant.
    private static void greedy(final Item.GreedyFactor factor) {
        final int MAX_WEIGHT = 67;
        final double[] WEIGHTS = { 23, 26, 20, 18, 32, 27, 29, 26, 30, 27};
        final double[] VALUES = { 505, 352, 458, 220, 354, 414, 498, 545, 473, 543 };

        // Fill up the heap according to the given factor with all 10 items.
        BinaryMaxHeap heap = new BinaryMaxHeap(factor);
        for (int i = 0; i < WEIGHTS.length; i++) {
            heap.insert(i, WEIGHTS[i], VALUES[i]);
        }

        System.out.println("Filling knapsack based on " + factor + "...");

        double totalWeight = 0; // Total weight in the knapsack so far
        double totalValue = 0; // Total value in the knapsack so far
        int itemCount = 0; // How many items are in the knapsack at the moment
        Item[] items = new Item[10];
        // Keep iterating until the knapsack is full.
        // This will never actually hit because of the break statements in the loop.
        while (totalWeight < MAX_WEIGHT) {
            Item curr = heap.deleteMax(); // Get the next-highest priority item.
            if (curr == null) // Heap is empty...
                break;
            // Make sure the item will not overload the knapsack's capacity:
            if (curr.weight + totalWeight <= MAX_WEIGHT) {
                items[itemCount] = curr; // Add item to array
                // Increment counters
                itemCount++;
                totalWeight += curr.weight;
                totalValue += curr.value;
            }
            // We can't add another item. Exit the loop.
            else
                break;
        }

        // Print the selected items, and the total value in the knapsack.
        for (Item item : items) {
            if (item == null)
                break;
            item.print();
        }
        System.out.println("Total value: " + totalValue);
        System.out.println();
    }
}
