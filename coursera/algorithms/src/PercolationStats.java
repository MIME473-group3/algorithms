public class PercolationStats {
	
	private double[] mins;
	private double m;
	private double std;
	
	// perform T independent computational experiments on an N-by-N grid
	// The constructor should throw a java.lang.IllegalArgumentException if either N ≤ 0 or T ≤ 0.
   public PercolationStats(int N, int T) {
	   if(N <= 0) throw new IllegalArgumentException("N <= 0");
	   if(T <= 0) throw new IllegalArgumentException("T <= 0");
	   
	   mins = new double[T];
	   
	   for(int t = 0; t < T; ++t) {
		   
		   Percolation p = new Percolation(N);
		   int open = 0;
		   while(!p.percolates()) {
			   
			   int i = StdRandom.uniform(N) + 1;
			   int j = StdRandom.uniform(N) + 1;
			   if(!p.isOpen(i, j)) {
				   p.open(i, j);
				   open++;
			   }
		   }
		   
		   mins[t] = (double)open / (N * N);
	   }   
	   
	   m = 0;
	   for(double i : mins)
		   m += i;
	   m /= mins.length;
	   
	   if(T == 1) 
		   std = Double.NaN;
	   else {
		   std = 0;
		   for(double i : mins) 
			   std += (i - m) * (i - m);
		   
		   std = Math.sqrt(std / (mins.length - 1));		 
	   }
   }
   
   // sample mean of percolation threshold
   public double mean() {
	   
	   return m;
   }
   
   // sample standard deviation of percolation threshold
   public double stddev() {
	   
	   return std;
   }
   
   // returns lower bound of the 95% confidence interval
   public double confidenceLo() {
	   
	   return m - 1.96 * std / Math.sqrt(mins.length);
   }
   
   // returns upper bound of the 95% confidence interval
   public double confidenceHi() {
	   
	   return m + 1.96 * std / Math.sqrt(mins.length);
   }
   
//    test client, described below
//    Also, include a main() method that takes two command-line arguments N and T, performs T independent
//    computational experiments (discussed above) on an N-by-N grid, and prints out the mean, standard deviation, 
//    and the 95% confidence interval for the percolation threshold. Use standard random from our standard libraries
//   to generate random numbers; use standard statistics to compute the sample mean and standard deviation.
//   % java PercolationStats 2 100000
//   mean                    = 0.6669475
//   stddev                  = 0.11775205263262094
//   95% confidence interval = 0.666217665216461, 0.6676773347835391
   public static void main(String[] args) {
	   
	   int N = 2;
	   int T = 10;
	   
	   int times = 100;
	   
	   for(int i = 0; i < times; ++i) {
		   
		   Stopwatch s = new Stopwatch();
		   
		   new PercolationStats(N, T);
		   
		   System.out.println("N\t=\t" + Integer.toString(N) + "\tTook\t=\t" + Double.toString(s.elapsedTime()));
		   N *= 2;
	   }

   }
}

