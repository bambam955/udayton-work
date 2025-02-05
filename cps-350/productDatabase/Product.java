package productDatabase;

public class Product {
    // The data for each product is abstracted into a separate class to make operations easier,
    // like swapping and constructing.
    public ProductData data = null;
    public Product next = null;

    // Default constructor.
    public Product() {}

    // Constructor to create a new product with all its data.
    public Product(long id, String name, double original, double current, Product next)
    {
        this.data = new ProductData(id, name, original, current);
        this.next = next;
    }
    // Constructor for creating a new product with a null next node.
    public Product(long id, String name, double original, double current)
    {
        this(id, name, original, current, null);
    }
    // Constructor for creating a new product from other product (performs a deep copy).
    public Product(final Product other)
    {
        this.data = other.data;
        this.next = other.next;
    }
}
