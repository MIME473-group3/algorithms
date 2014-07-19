import java.util.LinkedHashSet;
import java.util.Set;

/**
 * Created by adam on 06/03/14.
 */


public class Solver {

    private MinPQ<Step> pq;
    private Set<Board> visited;
    private Board start;
    private int moves;
    private boolean solved;


    public Solver(Board initial)            // find a solution to the initial board (using the A* algorithm)
    {
        visited = new LinkedHashSet<Board>();
        pq = new MinPQ<Step>();
        solved = solve(initial);
    }

    public boolean isSolvable()             // is the initial board solvable?
    {
        return solved;
    }

    public int moves()                      // min number of moves to solve initial board; -1 if no solution
    {
        return moves;
    }

    public Iterable<Board> solution()       // sequence of boards in a shortest solution; null if no solution
    {
        return visited;
    }

    private boolean solve(Board board) {


        moves = 0;
        pq.insert(new Step(board.manhattan() + moves, board));
        Board next = null;
        try {
        do {
            next = pq.delMin().board;
            visited.add(next);

            ++moves;
            pq = new MinPQ();
            for(Board b : next.neighbors()) {
                if(!visited.contains(b)) {
                    pq.insert(new Step(b.manhattan() + moves, b));
                }

            }

        } while(!next.isGoal());

        return true;
        } catch (Exception e) {
            return false;
        }
    }

    private class Step implements Comparable<Step> {

        public int score;
        public Board board;

        public Step(int score, Board board) {
            this.score = score;
            this.board = board;
        }

        public int compareTo(Step that) {

            if(this == that || this.score == that.score) return 0;
            if(this.score < that.score) return -1;
            return 1;
        }
    }

 // solve a slider puzzle (given below)
    public static void main(String[] args) {
        // create initial board from file
//        In in = new In("Algorithms/resources/8puzzle/puzzle04.txt");
        In in = new In(args[0]);
        int N = in.readInt();
        int[][] blocks = new int[N][N];
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                blocks[i][j] = in.readInt();
        Board initial = new Board(blocks);

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }
}

