package tester;

import java.util.Random;

public class MergeSortThreaded {

    public static double[] finalMerge(double[] a, double[] b) {
        double[] result = new double[a.length + b.length];
        int i=0;
        int j=0;
        int r=0;
        while (i < a.length && j < b.length) {
            if (a[i] <= b[j]) {
                result[r]=a[i];
                i++;
                r++;
            } else {
                result[r]=b[j];
                j++;
                r++;
            }
            if (i==a.length) {
                while (j<b.length) {
                    result[r]=b[j];
                    r++;
                    j++;
                }
            }
            if (j==b.length) {
                while (i<a.length) {
                    result[r]=a[i];
                    r++;
                    i++;
                }
            }
        }
        return result;
    }

    public static void main(String[] args) throws InterruptedException {
    		Random r = new Random();
    		double temp;
        double[] original = new double[Integer.parseInt(args[0])];
        double[] original2 = new double[Integer.parseInt(args[0])];
        for (int i=0; i<original.length; i++) {
        		temp = 1 + (100 - 1) * r.nextDouble();
            original[i] = temp;
            original2[i] = temp;
        }

        double[] subArr1 = new double[original.length/2];
        double[] subArr2 = new double[original.length - original.length/2];
        System.arraycopy(original, 0, subArr1, 0, original.length/2);
        System.arraycopy(original, original.length/2, subArr2, 0, original.length - original.length/2);
        Worker runner1 = new Worker(subArr1);
        Worker runner2 = new Worker(subArr2);
      //Double thread
        long startTime = System.currentTimeMillis();
        runner1.start();
        runner2.start();
        runner1.join();
        runner2.join();
        original = finalMerge(runner1.getInternal(), runner2.getInternal());
        long stopTime = System.currentTimeMillis();
      //Calculation
        long elapsedTime = stopTime - startTime;
        System.out.println("Sorting is done in " + (float)elapsedTime + "ms when two threads are used");

      //SINGLE Thread
        long startTime2 = System.currentTimeMillis();
        sort(original2);
        long stopTime2 = System.currentTimeMillis();

        long elapsedTime2 = stopTime2 - startTime2;
        System.out.println("Sorting is done in " + (float)elapsedTime2 + "ms when one thread is used");
    }
    public static void sort(double[] original2) {
		double temp;
		for(int i = 0; i < original2.length-1; i++) {
			for(int j = 0; j < original2.length-1-i; j++) {
				if(original2[j] > original2[j+1]) {
					temp = original2[j];
					original2[j] = original2[j+1];
					original2[j+1] = temp;
				}
			}
		}
	}

}
