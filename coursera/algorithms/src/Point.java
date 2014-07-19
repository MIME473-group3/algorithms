/*************************************************************************
 * Name:
 * Email:
 *
 * Compilation:  javac Point.java
 * Execution:
 * Dependencies: StdDraw.java
 *
 * Description: An immutable data type for points in the plane.
 *
 *************************************************************************/

import java.util.Arrays;
import java.util.Comparator;

public class Point implements Comparable<Point> {

    // compare points by slope
    public final Comparator<Point> SLOPE_ORDER = new Comparator<Point>() {
    	
		@Override
		public int compare(Point p1, Point p2) {

            double slope1 = slopeTo(p1);
            double slope2 = slopeTo(p2);
			if(slope1 < slope2) return -1;
			if(slope1 > slope2) return 1;
			return 0;
		}
    };

    private final int x;                              // x coordinate
    private final int y;                              // y coordinate

    // create the point (x, y)
    public Point(int x, int y) {
        /* DO NOT MODIFY */
        this.x = x;
        this.y = y;
    }

    // plot this point to standard drawing
    public void draw() {
        /* DO NOT MODIFY */
        StdDraw.filledCircle(x, y, 200);
//      StdDraw.point(x, y);
    }

    // draw line between this point and that point to standard drawing
    public void drawTo(Point that) {
        /* DO NOT MODIFY */
        StdDraw.line(this.x, this.y, that.x, that.y);
    }

    // slope between this point and that point
    public double slopeTo(Point that) {
        if(this == that || (this.y == that.y && this.x == that.x))
            return Double.NEGATIVE_INFINITY;
        if(this.y == that.y) return (1.0 - 1.0) / 1.0;
        if(this.x == that.x) return Double.POSITIVE_INFINITY;
        return (double)(that.y - this.y) / (that.x - this.x);
    }

    // is this point lexicographically smaller than that one?
    // comparing y-coordinates and breaking ties by x-coordinates
    public int compareTo(Point that) {
        if(this == that || (this.y == that.y && this.x == that.x)) return 0;
        if(this.y < that.y || (this.y == that.y && this.x < that.x)) return -1;
        //if(this.y > that.y || this.y == that.y && this.x > that.x)
        return 1;
    }

    // return string representation of this point
    public String toString() {
        /* DO NOT MODIFY */
        return "(" + String.valueOf(x) + ", " + String.valueOf(y) + ")";
    }

    // unit test
    public static void main(String[] args) {

        Point point = new Point(10, 10);
        System.out.println(point);

        Point ps[] = new Point[10];
        for(int i = 0; i < 10; ++i) ps[i] = new Point(StdRandom.uniform(100), StdRandom.uniform(100));
        for(Point p : ps) System.out.print(p + " "); System.out.println();
        Arrays.sort(ps, 0, ps.length);
        for(Point p : ps) System.out.print(p + " "); System.out.println();
        Arrays.sort(ps, 0, ps.length, point.SLOPE_ORDER);
        for(Point p : ps) System.out.print(p + " "); System.out.println();


        Point points[] = new Point[] { new Point(29000, 8000), new Point(26000, 10000), new Point(16000, 16000), new Point(5000, 18000)};
        for(int i = 0; i < points.length - 1; ++i)
            System.out.println(points[i].slopeTo(points[i + 1]));


        System.out.println(new Point(1, 1).slopeTo(new Point(-1, -1)));

        for(int i = 1; i < 10; ++i) ps[i] = new Point(1, i);
        ps[0] = new Point(0, 0);
        for(Point p : ps) System.out.print(p + " "); System.out.println();
        Arrays.sort(ps, 1, ps.length, point.SLOPE_ORDER);
        for(Point p : ps) System.out.print(p + " "); System.out.println();




    }
}