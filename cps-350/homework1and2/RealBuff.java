package homework1and2;

class RealBuff {
    static final int max_size = 100; // The default maximum size of the buffer
    double[] content; // The content of the buffer
    int current_size; // The number of valid elements currently contained in the buffer

    // Initialize an empty buffer with the default maximum size
    RealBuff() {
        content = new double[max_size];
        current_size = 0;
    }

    // Initialize an empty buffer with the maximum size given by n
    RealBuff(final int n) {
        content = new double[n];
        current_size = 0;
    }

    // Initialize a buffer which is a copy of "buff"
    RealBuff(final RealBuff buff) {
        content = new double[buff.content.length];
        current_size = buff.current_size;
        for (int i = 0; i < current_size; i++) {
            content[i] = buff.content[i];
        }
    }

    // Append a value to the end of the buffer
    // NOTE: the value will not be appended if the buffer is full
    public boolean append(double value) {
        if (current_size >= content.length)
            return false;
        
        content[current_size] = value;
        current_size++;
        return true;
    }

    // Insert a value at a given position in the buffer. Elements will be shifted as needed to make space.
    // NOTE: the value will not be inserted if the buffer is full, or if the desired position
    //       would put empty spaces between values (e.g. current size is 2, insert at 12).
    public boolean insertAt(int position, double value) {
        if (position >= current_size || current_size >= content.length)
            return false;

        double[] newContent = new double[content.length];
        
        // Increment current_size now so that each element of newContent gets filled
        current_size++;

        for (int i = 0; i < current_size; i++) {
            if (i < position)
                newContent[i] = content[i];
            else if (i == position)
                newContent[i] = value;
            else
                newContent[i] = content[i - 1];
        }

        content = newContent;
        return true;
    }

    // Remove the value at a given position in the buffer. 
    // Elements will be shifted as needed to make sure there are no empty spaces.
    public boolean removeAt(int position) {
        if (current_size == 0)
            return false;

        double[] newContent = new double[content.length];

        for (int i = 0; i < current_size; i++) {
            if (i < position)
                newContent[i] = content[i];
            else if (i == position)
                continue; // Skip the element to be removed
            else
                newContent[i - 1] = content[i];
        }

        content = newContent;

        // Don't decrement until after filling the new content so that we get all elements of the old content
        current_size--;
        return true;
    }

    // Print a formatted string containing all valid elements in the buffer.
    public void print() {
        String str = "[ ";
        for (int i = 0; i < current_size; i++) {
            str += (content[i] + ", ");
        }
        str = str.substring(0, str.length() - 2); // Remove the last comma and space
        str += " ]";
        System.out.println(str);
    }

    // Sort the buffer in ascending order using the insertion sort algorithm.
    // NOTE: invalid/empty elements are not included in the sort.
    public void insertionSort() {
        int i = 0;
        double key = 0;
        // Iterate through each element, skipping the first one.
        for (int j = 1; j < current_size; j++) {
            key = content[j];
            i = j - 1;
            // Go backwards from the current index, checking the key against content[i]
            // until an element smaller than the key is found. Shift each larger element up one index.
            while (i >= 0 && content[i] > key) {
                content[i + 1] = content[i];
                i--;
            }
            // Place the key in the proper position.
            content[i + 1] = key;
        }
    }

    // Quicksort algorithm
    public void quicksort() {
        // Wrapper to start quicksort with the entire buffer
        quicksortHelper(content, 0, current_size - 1);
    }
    private void quicksortHelper(double[] a, int low, int high) {
        // Base case: array to be sorted has size < 0
        if (high < low)
            return;
        int q = quicksortPartition(a, low, high);
        quicksortHelper(a, low, q - 1);
        quicksortHelper(a, q + 1, high);
    }
    private int quicksortPartition(double[] a, int low, int high) {
        // Pivot is the last element in the subarray.
        double pivot = a[high];
        int i = low - 1;
        // Iterate through the entire subarray. Swap i and j if j is less than the pivot.
        // By the end, all elements less than the pivot 
        // will be at indices below all the elements greater than the pivot.
        for (int j = low; j < high; j++) {
            if (a[j] <= pivot) {
                i++;
                // Swap a[i] and a[j]
                double tmp1 = a[i];
                a[i] = a[j];
                a[j] = tmp1;
            }
        }
        // Swap a[i + 1] and a[high]. This puts the pivot in its proper place.
        double tmp2 = a[i + 1];
        a[i + 1] = a[high];
        a[high] = tmp2;

        return i + 1;
    }

    // Mergesort algorithm
    public void mergesort() {
        // Wrapper to start mergesort with the entire buffer
        content = mergesortHelper(content, current_size);
    }
    private double[] mergesortHelper(double[] a, int length) {
        // Base case: don't need to sort a subarray with 0 or 1 elements.
        if (length < 2)
            return a;
        // Determine the midpoint index.
        int m = length / 2;
        // Create auxiliary array of all elements below midpoint.
        double[] p1 = new double[m];
        for (int i = 0; i < m; i++) {
            p1[i] = a[i];
        }
        // Create a second auxiliary array of all elements above midpoint.
        double[] p2 = new double[length - m];
        for (int i = m; i < length; i++) {
            p2[i - m] = a[i];
        }

        // Divide the array again.
        double[] q1 = mergesortHelper(p1, m);
        double[] q2 = mergesortHelper(p2, length - m);
        // Merge the two subarrays.
        return mergesortMerge(q1, q2);  
    }
    private double[] mergesortMerge(double[] a, double[] b) {
        int i = 0, j = 0, k = 0;
        double[] temp = new double[a.length + b.length];
        // While both arrays still have elements left, add in the smallest one.
        // Both arrays are sorted, so we can go from low to high index.
        while (i < a.length && j < b.length) {
            if (a[i] <= b[j])
                temp[k++] = a[i++];
            else
                temp[k++] = b[j++];
        }
        // Once one array runs out of elements, append whatever is left in the other one.
        while (i < a.length)
            temp[k++] = a[i++];
        while (j < b.length)
            temp[k++] = b[j++];
        return temp;
    }
}
