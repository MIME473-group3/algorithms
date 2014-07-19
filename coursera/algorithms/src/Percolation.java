//  all methods should take constant time plus a constant number of calls to the union-find methods union(), find(), connected(), and count().
public class Percolation {
	
	private int N;
	private byte data[]; //opened p = 0, conToTop p = 1, conToBot p = 2;
	private WeightedQuickUnionUF uf;
	private int source;
	private static final int OPEN = 0;
	private static final int BOTTOM = 1;
	
	// create N-by-N grid, with all sites blocked, ~N^2;
	public Percolation(int N) {
	   this.N = N;
	   uf = new WeightedQuickUnionUF(N * N + 1);
	   data = new byte[N*N + 1];
	   source = index(N, N) + 1; 
	}
	
	public void open(int i, int j) {
		int ind = index(i, j);
		if(get(ind, OPEN)) return;
			
		set(ind, OPEN);
		if(i == 1) uf.union(ind, source);
		if(i == N) set(ind, BOTTOM);	
		
		
		int neighbours[] = new int[] { j > 1 ? ind - 1 : -1,
									j < N ? ind + 1 : -1,
									i > 1 ? ind - N : -1,
									i < N ? ind + N : -1};	
		
		for(int n : neighbours) {
			
			if(n != -1 && get(n, OPEN)) {
				
				uf.union(ind, n);					
				if(get(ind, BOTTOM)) set(n, BOTTOM); 
				else if(get(n, BOTTOM)) set(ind, BOTTOM);
			}
		}			
		
		 
		if(get(ind, BOTTOM)) set(uf.find(ind), BOTTOM);
		
		
	}
   
	// is site (row i, column j) open?
	public boolean isOpen(int i, int j) {
		return get(index(i, j), OPEN);
	}
   
	// is site (row i, column j) full?
	public boolean isFull(int i, int j) {
		
		return uf.connected(index(i, j), source);
	}
   
	// does the system percolate?
	public boolean percolates() {
		return get(uf.find(source), BOTTOM);
	}
	
	private int index(int i, int j) {
		if(i < 1 || i > N) throw new IndexOutOfBoundsException("row index out of bound: " + Integer.toString(i));
		if(j < 1 || j > N) throw new IndexOutOfBoundsException("column index out of bound: " + Integer.toString(j));
		
		return (i - 1) * N + j - 1;		
	}	
	
	
	private void set(int index, int pos) {
		
		data[index] = (byte) (data[index] | (1 << pos));
	}
	
	private boolean get(int index, int pos) {
		
		return (data[index] & (1 << pos)) == 1; 
	}
	
	public void printData() {
		
		for(int i = 1; i <= N; ++i) {
			for(int j = 1; j <= N; ++j)
				System.out.print(Byte.toString(data[index(i, j)]) + " ");
			System.out.println();
		}
	}
	
	public static void main(String[] args) {
		
		int N = 5;
		Percolation p = new Percolation(N);
		System.out.println("Percolates: " + Boolean.toString(p.percolates()));
		System.out.println();
		System.out.println();
		for(int i = 1; i <= N; ++i) {
//			for(int j = i; j < N + 1; ++j)
			p.open(i, i);
			if(i < N) p.open(i, i + 1);
		}
		
		p.open(N, 1);
		p.open(N - 1, 2);
		p.open(N - 1, 1);
		
		for(int i = 1; i < N + 1; ++i) {
			for(int j = 1; j < N + 1; ++j) {
				System.out.print(p.isOpen(i, j) ? "1 " : "0 ");
			}
			System.out.println();
		}
		System.out.println();
		System.out.println();
		
		for(int i = 1; i < N + 1; ++i) {
			for(int j = 1; j < N + 1; ++j) {
				System.out.print(p.isFull(i, j) ? "1 " : "0 ");
			}
			System.out.println();
		}		
		System.out.println();
		System.out.println();
		
		p.printData();
		
		System.out.println("Percolates: " + Boolean.toString(p.percolates()));
	}
}
