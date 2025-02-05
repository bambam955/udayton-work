package countyDatabase;

public class County {
    String name;
    int fips;
    String seat;
    long population;
    double area;

    public County(String _name, String _fips, String _seat, long _population, double _area) {
        name = _name;
        fips = Integer.parseInt(_fips);
        seat = _seat;
        population = _population;
        area = _area;
    }

    // Print the county's information in a single line.
    public void print() {
        String str = "Name: " + name;
        // Format the FIPS code with leading zeroes if needed.
        String fipsStr = String.format(" FIPS: %03d", fips);
        str += fipsStr;
        str += (" Seat: " + seat);
        // Format the population with commas on the thousands.
        String populationStr = String.format(" Population: %,d", population);
        str += populationStr;
        str += (" Area: " + area);
        System.out.println(str);
    }
}
