import java.util.Arrays;

public class Brute {

    private static Point[] readPoints(String filename) {

        In in = new In(filename);
        int N = in.readInt();
        Point p[] = new Point[N];
        for (int i = 0; i < N; i++)
            p[i] = new Point(in.readInt(), in.readInt());
        return p;
    }

	public static void main(String[] args) {

    // rescale coordinates and turn on animation mode
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);

//         String filename =  args[0];
        String filename =  "Algorithms/resources/collinear/input8.txt";
        

        Point p[] = readPoints(filename);
        for(Point point : p) point.draw();

        for(int i = 0; i < p.length; ++i) {
            for(int j = i + 1; j < p.length; ++j) {

                double slope = p[i].slopeTo(p[j]);
                for(int k = j + 1; k < p.length; ++k) {

                    if(slope != p[j].slopeTo(p[k])) continue;
                     for(int l = k + 1; l < p.length; ++l) {

                        if(slope != p[k].slopeTo(p[l])) continue;
                        Point toDraw[] = new Point[] {p[i], p[j], p[k], p[l]};
                        Arrays.sort(toDraw, 0, 4);
                        toDraw[0].drawTo(toDraw[3]);
                        System.out.println(toDraw[0] + " -> " + toDraw[1] + " -> " + toDraw[2] + " -> " + toDraw[3]);
                    }
                }
            }    
        }

        // display to screen all at once
        StdDraw.show(0);
	}
}
