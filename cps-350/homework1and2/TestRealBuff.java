package homework1and2;

import java.util.Random;

// Following the test steps given in the assignment. Each step corresponds to a comment.

class TestRealBuff
{
    public static void main(String[] args)
    {
        // Make sure both algorithms are working right.
        testQuicksortFunctionality();
        testMergesortFunctionality();

        // Test how long each algorithm takes with very large datasets.
        testQuicksortComplexity();
        testMergesortComplexity();
    }

    private static void testQuicksortFunctionality() {
        System.out.println("\nTesting quicksort works properly...");
        // Create new buffer object.
        RealBuff buff1 = new RealBuff();
        // Create new random number generator. Add ten random numbers to the buffer.
        // NOTE: I used nextInt() so the values would be easier to read.
        Random random = new Random();
        for (int i = 0; i < 10; i++) {
            buff1.append(random.nextInt(100));
        }
        // Print the unsorted buffer.
        buff1.print();
        // Sort the buffer using the quicksort algorithm.
        buff1.quicksort();
        // Print the unsorted buffer.
        buff1.print();
    }
    private static void testMergesortFunctionality() {
        System.out.println("\nTesting mergesort works properly...");
        // Create new buffer object.
        RealBuff buff1 = new RealBuff();
        // Create new random number generator. Add ten random numbers to the buffer.
        // NOTE: I used nextInt() so the values would be easier to read.
        Random random = new Random();
        for (int i = 0; i < 10; i++) {
            buff1.append(random.nextInt(100));
        }
        // Print the unsorted buffer.
        buff1.print();
        // Sort the buffer using the quicksort algorithm.
        buff1.mergesort();
        // Print the unsorted buffer.
        buff1.print();
    }
    
    private static void testQuicksortComplexity() {
        System.out.println("\nTesting time complexity of quicksort...");
        // Create 10 new buffers, each with 500,000 random elements between -100 and 100.
        Random random = new Random();
        RealBuff[] buffs = new RealBuff[10];
        final int BUFF_LENGTH = 1_000_000;
        for (int i = 0; i < buffs.length; i++) {
            buffs[i] = new RealBuff(BUFF_LENGTH);
            for (int j = 0; j < BUFF_LENGTH; j++) {
                buffs[i].append(random.nextInt(201) - 100);
            }
        }
        // Find the average time required to sort the buffers using quicksort.
        long totalTime = 0;
        for (int i = 0; i < buffs.length; i++) {
            long now = System.currentTimeMillis();
            buffs[i].quicksort();
            totalTime += (System.currentTimeMillis() - now);
        }
        double avgTime = totalTime / buffs.length;
        System.out.println("Average time to complete quicksort: " + avgTime + "ms");
    }
    private static void testMergesortComplexity() {
        System.out.println("\nTesting time complexity of mergesort...");
        // Create 10 new buffers, each with 500,000 random elements between -100 and 100.
        Random random = new Random();
        RealBuff[] buffs = new RealBuff[10];
        final int BUFF_LENGTH = 1_000_000;
        for (int i = 0; i < buffs.length; i++) {
            buffs[i] = new RealBuff(BUFF_LENGTH);
            for (int j = 0; j < BUFF_LENGTH; j++) {
                buffs[i].append(random.nextInt(201) - 100);
            }
        }
        // Find the average time required to sort the buffers using mergesort.
        long totalTime = 0;
        for (int i = 0; i < buffs.length; i++) {
            long now = System.currentTimeMillis();
            buffs[i].mergesort();
            totalTime += (System.currentTimeMillis() - now);
        }
        double avgTime = totalTime / buffs.length;
        System.out.println("Average time to complete mergesort: " + avgTime + "ms");
    }
}