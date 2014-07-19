package custom;

/**
 * Created by adam on 3/14/14.
 */

public class Sort {


    public static void mergeSort(int[] T) {

            int[] A = new int[T.length];
        for(int i = 0; i < T.length; ++i) {
            A[i] = T[i];
        }

        mergeSortImpl(T, A, 0, T.length / 2, T.length);
    }

    private static void mergeSortImpl(int[] T, int[] A, int lo, int mid, int hi) {

        if(mid - lo > 1) mergeSortImpl(T, A, lo, mid / 2, mid);
        if(hi - mid > 1) mergeSortImpl(T, A, mid, mid + (hi - mid) / 2, hi);
        merge(T, A, lo, mid, hi);
    }

    private static void merge(int[] T, int[] A, int lo, int mid, int hi) {

        int i = lo;
        int j = mid;

        for(int k = lo; k < hi; ++k) {

            if(j == hi) T[k] = A[i++];
            else if(i == mid) T[k] = A[j++];
            else if(A[i] <= A[j]) T[k] = A[i++];
            else if(A[i] > A[j]) T[k] = A[j++];
        }
    }

    public static void quickSort(int[] T) {


    }

    public static void heapSort(int[] T) {


    }

    public static void insertionSort(int[] T) {

        for(int i = 0; i < T.length; ++i) {
            int min = i;
            for(int j = i; j < T.length; ++j) {
                if(T[i] > T[j]) {
                    swap(T, i, j);
                    min = j;
                }
            }
        }
    }

    public static void shellSort(int[] T) {


    }

    public static void selectionSort(int[] T) {
        for(int i = 0; i < T.length; ++i) {
            int min = T[i];
            int minInd = i;
            for(int j = i; j < T.length; ++j) {
                if(T[j] < min) {
                    min = T[j];
                    minInd = j;
                }
            }
            swap(T, i, minInd);
        }
    }

    public static void countSort(int[] T, int max) {

        int count[] = new int[max + 1];
        for(int i = 0; i < max + 1; ++i) {
            count[i] = 0;
        }

        for(int i = 0; i < T.length; ++i) {
            count[T[i]] += 1;
        }

        int k = 0;
        for(int i = 0; i < max + 1; ++i) {
            for(int j = 0; j < count[i]; ++j) {
                T[k++] = i;
            }
        }
    }

    private static void swap(int[] T, int i, int j) {

        int t = T[i];
        T[i] = T[j];
        T[j] = t;
    }

    public static void main(String args[]) {

        int N = 10;
        int T[] = new int[N];

        for(int i = 0 ; i < N; ++i) {

            T[i] = (i * 15) % 7 * 17 % 11;
            T[i] *= T[i] % 2 == 0 ? 1 : -1;
        }

        for(int t : T) System.out.print(t + " "); System.out.println();
        Sort.mergeSort(T);
        for(int t : T) System.out.print(t + " "); System.out.println();
    }
}
