import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by adam on 06/03/14.
 */
public class Board {

    private int blocks[];
    private int N;

  // construct a board from an N-by-N array of blocks
  // (where blocks[i][j] = block in row i, column j)
  public Board(int[][] blocks) {

      this.N = blocks.length;
      this.blocks = new int[N * N];
      for(int i = 0; i < N; ++i) {
          for(int j = 0; j < N; ++j) {
              this.blocks[i * N + j] = blocks[i][j];
          }
      }
  }

// board dimension N
    public int dimension() {

        return N;
    }

// number of blocks out of place
    public int hamming() {
        int score = 0;
        for(int i = 0; i < blocks.length; ++i) {
            if(blocks[i] != y(i) * N + x(i) + 1 && blocks[i] != 0)
                ++score;
        }
        return score;
    }

// sum of Manhattan distances between blocks and goal
    public int manhattan() {
        int score = 0;
        for(int i = 0; i < blocks.length; ++i) {
            if(blocks[i] == 0) continue;
            int y = (blocks[i]  - 1) / N;
            int x = (blocks[i] - 1) % N;
            score += Math.abs(y(i) - y) + Math.abs(x(i) - x);
        }
        return score;
    }

// is this board the goal board?
    public boolean isGoal() {
        return hamming() == 0;
    }

// a board obtained by exchanging two adjacent blocks in the same row
    public Board twin() {

        if(blocks[0] == 0 || blocks[1] == 0)
            return makeNeighbor(N, N + 1);
        return makeNeighbor(0, 1);
    }

    private int[] swap(int T[], int i, int j) {

        int t = T[i];
        T[i] = T[j];
        T[j] = t;
        return T;
    }

    private int[] copyBlocks() {

        int[] newBlocks = new int[blocks.length];
        for(int i = 0; i < blocks.length; ++i) {
                newBlocks[i] = blocks[i];
        }

        return newBlocks;
    }

// does this board equal y?
    public boolean equals(Object y) {
        if(this == y) return true;
        if(y == null) return false;

        return this.toString().equals(y.toString());
    }

// all neighboring boards
    public Iterable<Board> neighbors() {

        int z = Arrays.binarySearch(blocks, 0);

        int x = x(z);
        int y = y(z);

        Set<Board> set = new HashSet<Board>();
        if(y + 1 < N)
          set.add(makeNeighbor((y + 1) * N + (x), z));
        if(y - 1 >= 0)
            set.add(makeNeighbor((y - 1) * N + (x), z));
        if(x + 1 < N)
            set.add(makeNeighbor((y) * N + (x + 1), z));
        if(x - 1 >= 0)
            set.add(makeNeighbor((y) * N + (x - 1), z));

        return set;
    }

    private Board makeNeighbor(int i, int z) {

        int b[][] = new int[N][];
        for(int k = 0; k < N; ++k) {
            b[k] = new int[N];
            for(int l = 0; l < N; ++i) {
                b[k][l] = blocks[k * N + l];
            }
        }

        int tmp = b[y(i)][x(i)];
        b[y(i)][x(i)] = b[y(z)][x(z)];
        b[y(z)][x(z)] = tmp;
        return new Board(b);
    }

// string representation of the board (in the output format specified below)
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(N + "\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                s.append(String.format("%2d ", blocks[i * N + j]));
            }
            s.append("\n");
        }
        return s.toString();
    }

    private int x(int i) {
        return i / N;
    }

    private int y(int i) {
        return i % N;
    }

    public static void main(String[] args) {

        int N = 3;;
        int blocks[][] = new int[N][];
        System.out.println("Board fields:");
        for(int i = 0; i < N; ++i) {
            blocks[i] = new int[N];
            for(int j = 0; j < N; ++j) {
                blocks[i][j] = i * N + j;
                System.out.print(blocks[i][j] + " ");
            }
            System.out.println();
        }

        System.out.println("Creating Board");
        Board board = new Board(blocks);
        System.out.println(board);


        System.out.println("Twin:");
        Board twin = board.twin();
        System.out.println(twin);
        assert(!twin.equals(board));

        System.out.println("Neighbours:");
        for(Board b : board.neighbors()) {
            System.out.println("Hamming = " + b.hamming() + " Manhattan = " + b.manhattan());
            System.out.println(b);

        }

        System.out.println("Board fields:");
        blocks[0] = new int[] {1, 0, 2};
        blocks[1] = new int[] {3, 4, 5};
        blocks[2] = new int[] {6, 7, 8};
        for(int i = 0; i < N; ++i) {

            for(int j = 0; j < N; ++j) {
                System.out.print(blocks[i][j] + " ");
            }
            System.out.println();
        }

        System.out.println("Creating Board");
        board = new Board(blocks);
        System.out.println(board);


        System.out.println("Twin:");
        twin = board.twin();
        System.out.println(twin);
        assert(!twin.equals(board));

        System.out.println("Neighbours:");
        for(Board b : board.neighbors()) {
            System.out.println("Hamming = " + b.hamming() + " Manhattan = " + b.manhattan());
            System.out.println(b);

        }
    }
}