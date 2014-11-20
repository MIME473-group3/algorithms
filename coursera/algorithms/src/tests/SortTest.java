//package tests;
//
//import org.testng.Assert;
//import org.testng.annotations.BeforeMethod;
//import org.testng.annotations.BeforeTest;
//import org.testng.annotations.Test;
//
//import custom.Sort;
//
///**
// * Created by adam on 3/14/14.
// */
//public class SortTest {
//
//    private int[] T;
//    private static final int N = 10;
//
//    private static boolean isSorted(int[] T) {
//
//        for(int i = 1; i < T.length; ++i)
//            if(T[i] > T[i - 1]) return false;
//
//        return true;
//    }
//
//    @BeforeMethod
//    public void setUp() {
//
//        T = new int[N];
//
//        for(int i = 0 ; i < N; ++i) {
//
//            T[i] = (i * 15) % 7 * 17 % 11;
//            T[i] *= T[i] % 2 == 0 ? 1 : -1;
//        }
//    }
//
//
//    @Test
//    public void testMergeSort() throws Exception {
//
//       Sort.mergeSort(T);
//        Assert.assertTrue(isSorted(T));
//    }
//
//    @Test
//    public void testQuickSort() throws Exception {
//        Sort.quickSort(T);
//        Assert.assertTrue(isSorted(T));
//    }
//
//    @Test
//    public void testHeapSort() throws Exception {
//        Sort.heapSort(T);
//        Assert.assertTrue(isSorted(T));
//    }
//
//    @Test
//    public void testInsertionSort() throws Exception {
//
//        Sort.insertionSort(T);
//        Assert.assertTrue(isSorted(T));
//    }
//
//    @Test
//    public void testShellSort() throws Exception {
//        Sort.shellSort(T);
//        Assert.assertTrue(isSorted(T));
//    }
//
//    @Test
//    public void testSelectionSort() throws Exception {
//
//        Sort.selectionSort(T);
//        Assert.assertTrue(isSorted(T));
//    }
//
//    @Test
//    public void testCountSort() throws Exception {
//
//        System.out.println();
////        Sort.countSort(T, 1000000);
//        Assert.assertTrue(isSorted(T));
//    }
//}
