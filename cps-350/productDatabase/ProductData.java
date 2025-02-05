package productDatabase;

public class ProductData {
    // Save each of the properties of a product.
    public long id = 0;
    public String name = null;
    public double originalPrice = 0;
    public double currentPrice = 0;

    // Construct a new data object by initializing all fields.
    public ProductData(long id, String name, double original, double current) {
        this.id = id;
        this.name = name;
        this.originalPrice = original;
        this.currentPrice = current;
    }
    // Calculate the discount percentage of the current price.
    public double discount() {
        return (originalPrice - currentPrice) / originalPrice;
    }
}
