import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Fast {

    private static Point[] readPoints(String filename) {

        In in = new In(filename);
        int N = in.readInt();
        Point p[] = new Point[N];
        for (int i = 0; i < N; i++)
            p[i] = new Point(in.readInt(), in.readInt());
        return p;
    }

    private static String prepString(Point p[], int init, int n) {

        StringBuffer buffer = new StringBuffer();
        buffer.append(p[init]);
        for(int k = init + 1; k < init + n; ++k) {
            buffer.append(" -> " + p[k]);
        }
        return buffer.toString();
    }

    private static void checkAndOutput(Set<String> drawn, int sameSlope, Point p, Point sorted[], int init) {

        if(sameSlope >= 2) {

            int scope = sameSlope + 2;
            int first = init - scope;
//            sorted[first] = p;
//            Arrays.sort(sorted, first, first + scope);
            Point toDraw[] = new Point[scope];
            toDraw[0] = p;
            for(int i = 1, k = first + 1; i < scope; ++i, ++k) {
                toDraw[i] = sorted[k];
            }
            Arrays.sort(toDraw, 0, toDraw.length);


            String lines = prepString(toDraw, 0, toDraw.length);
//            String lines = prepString(sorted, init - scope, scope);
            if(!drawn.contains(lines)) {
                drawn.add(lines);
                System.out.println(lines);
//                sorted[first].drawTo(sorted[init - 1]);
                toDraw[0].drawTo(toDraw[toDraw.length - 1]);
            }

        }
    }

    private static void swap(Point p[], int i, int j) {

        Point t = p[i];
        p[i] = p[j];
        p[j] = t;
    }


	public static void main(String[] args) {

        // rescale coordinates and turn on animation mode
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);

        String filename =  "Algorithms/resources/collinear/input50.txt";
//        String filename =  args[0];

        HashSet<String> drawn = new HashSet<String>();

        Point p[] = readPoints(filename);
        Point sorted[] = new Point[p.length];

        Arrays.sort(p, 0, p.length);
        for(int i = 0; i < p.length; ++i) {
            p[i].draw();
            sorted[i] = p[i];
        }
 
        for(int i = 0; i < p.length; ++i) {
//            Arrays.sort(sorted, 0, p.length);
            Arrays.sort(sorted, 0, p.length, p[i].SLOPE_ORDER);
            double sOld = p[i].slopeTo(p[i]);
            double sNew = Double.NaN;
            int sameSlope = 0;
            for(int j = i; j < p.length; ++j) {

                sNew = p[i].slopeTo(sorted[j]);
                if(sOld == sNew) {
                    ++sameSlope;
                } else {

                    checkAndOutput(drawn, sameSlope, p[i], sorted, j);
                    sameSlope = 0;
                }
                sOld = sNew;
            }

            checkAndOutput(drawn, sameSlope, p[i], sorted, p.length);
        }

        // display to screen all at once
        StdDraw.show(0);
    }
}
