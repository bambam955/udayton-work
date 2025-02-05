import java.math.*;

public class Item {
    int id; // Unique ID of the item
    double weight;
    double value;
    private GreedyFactor factorField; // Determines what value to use for the priority of the item

    // The priority of the item can be one of three values...
    enum GreedyFactor {
        VALUE, // Highest value is highest priority
        WEIGHT, // Lowest weight is highest priority
        RATIO // Ratio of value to weight, i.e. largest value per weight is highest priority
    }

    // Constructor: give ID, weight, value, and priority determinant
    public Item(final int _id, final double _weight, final double _value, final GreedyFactor _factor) {
        id = _id;
        weight = _weight;
        value = _value;
        factorField = _factor;
    }

    // Use the priority determinant to determine the priority value.
    public double factor() {
        switch (factorField) {
            case VALUE:
                return value;
            case WEIGHT:
                return weight * -1; // So that lighter items are higher priority
            case RATIO:
                return value / weight;
            default:
                return -1; // Default case...not handled by the heap, just prevents build errors
        }
    }

    public void print() {
        // Round the value-to-weight ratio to two decimal places for ease of viewing.
        double roundedRatio = new BigDecimal(value / weight).setScale(2, RoundingMode.HALF_UP).doubleValue();
        // Print all the data of the item.
        System.out.println("ID: " + id + "\tWeight: " + weight + "\tValue: " + value + "\tRatio: " + roundedRatio);
    }
}
