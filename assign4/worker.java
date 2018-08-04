package tester;

public class Worker extends Thread {
    private double[] internal;

    public double[] getInternal() {
        return internal;
    }

    public void mergeSort(double[] array) {
        if (array.length > 1) {
            double[] left = leftHalf(array);
            double[] right = rightHalf(array);

            mergeSort(left);
            mergeSort(right);

            merge(array, left, right);
        }
    }

    public double[] leftHalf(double[] array) {
        int size1 = array.length / 2;
        double[] left = new double[size1];
        for (int i = 0; i < size1; i++) {
            left[i] = array[i];
        }
        return left;
    }

    public double[] rightHalf(double[] array) {
        int size1 = array.length / 2;
        int size2 = array.length - size1;
        double[] right = new double[size2];
        for (int i = 0; i < size2; i++) {
            right[i] = array[i + size1];
        }
        return right;
    }

    public void merge(double[] result, double[] left, double[] right) {
        int i1 = 0;
        int i2 = 0;

        for (int i = 0; i < result.length; i++) {
            if (i2 >= right.length || (i1 < left.length && left[i1] <= right[i2])) {
                result[i] = left[i1];
                i1++;
            } else {
                result[i] = right[i2];
                i2++;
            }
        }
    }

    Worker(double[] arr) {
        internal = arr;
    }

    public void run() {
        mergeSort(internal);
    }
}
