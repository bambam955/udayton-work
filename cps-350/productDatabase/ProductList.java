package productDatabase;

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class ProductList {
    // This is a dummy head.
    Product head = null;

    // Constructor for creating a database from a file.
    public ProductList(final String filePath) {
        // Make sure to catch errors if the file doesn't exist.
        try {
            this.head = new Product();
            Product iter = this.head;
            Scanner fileReader = new Scanner(new File(filePath));

            // Each iteration of the loop will parse another product from the file.
            while (fileReader.hasNextLine()) {
                // First we get the product ID.
                long id = fileReader.nextLong();
                fileReader.nextLine(); // Move to the next line.
                // Second we get the product name. This already gets the whole line.
                String name = fileReader.nextLine();
                // Third we get the original price.
                double original = fileReader.nextDouble();
                fileReader.nextLine(); // Move to the next line.
                // Finally we get the current price.
                double current = fileReader.nextDouble();
                // Create a new node in the linked list.
                iter.next = new Product(id, name, original, current);
                iter = iter.next;
            }
            fileReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + filePath);
        }
    }

    // Constructor for creating a database from another database (performs a deep copy).
    public ProductList(ProductList other) {
        this.head = new Product();
        Product newIter = this.head;
        for (Product iter = other.head.next; iter != null; iter = iter.next) {
            newIter.next = new Product(iter);
            newIter = newIter.next;
        }
    }

    // Print the current contents of the database.
    public void print() {
        for (Product iter = head.next; iter != null; iter = iter.next) {
            System.out.println(iter.data.id);
            System.out.println(iter.data.name);
            System.out.println(iter.data.originalPrice);
            System.out.println(iter.data.currentPrice);
            System.out.println();
        }
    }

    // Sort the database by product discount.
    // The selection sort algorithm is used for sorting.
    public void sortByDiscount() {
        // Iterate through the entire list starting with the first product.
        for (Product curr = head.next; curr != null; curr = curr.next) {
            // Initialize the minimum to the current product.
            Product min = curr;

            // Find the smallest discount to the "right" of the current product.
            for (Product inner = curr.next; inner != null; inner = inner.next) {
                if (inner.data.discount() < min.data.discount())
                    min = inner;
            }

            // If the minimum product to the right isn't the current node then swap their data.
            if (min != curr) {
                ProductData tmp = curr.data;
                curr.data = min.data;
                min.data = tmp;
            }
        }
    }
}
