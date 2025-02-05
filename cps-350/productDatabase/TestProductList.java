package productDatabase;

public class TestProductList {
    public static void main(String[] args)
    {
        // Create a product database from the products.txt file.
        // Make sure the file is in a spot where the program can find it.
        // I put mine in the same directory as the "productDatabase" package directory.
        ProductList list = new ProductList("products.txt");
        System.out.println("Printing unsorted database...");
        list.print();

        // Make a deep copy of the database.
        ProductList list2 = new ProductList(list);
        System.out.println("Printing copied database...");
        list2.print();

        // Re-organize the products in the list in ascending order of discount.
        list2.sortByDiscount();
        System.out.println("Printing sorted database...");
        list2.print();
    }
}
