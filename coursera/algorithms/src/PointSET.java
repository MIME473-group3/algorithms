import java.util.HashSet;
import java.util.TreeSet;

public class PointSET {

    private TreeSet<Point2D> tree;

    // construct an empty set of points
    public PointSET() {
        tree = new TreeSet<Point2D>();
    }

    // is the set empty?
    public boolean isEmpty() {
        return tree.isEmpty();
    }

    // number of points in the set
    public int size() {
        return tree.size();
    }

    // add the point to the set (if it is not already in the set)
    // O(log(n))
    public void insert(Point2D p) {
        tree.add(p);
    }

    // does the set contain point p?
    // O(log(n))
    public boolean contains(Point2D p) {
        return tree.contains(p);
    }

    // draw all points to standard draw
    public void draw() {
        for(Point2D p : tree) {
            p.draw();
        }
    }

    // all points that are inside the rectangle
    // O(N)
    public Iterable<Point2D> range(RectHV rect) {
        HashSet<Point2D> set = new HashSet<Point2D>();
        for(Point2D p : tree) {
            if(p.x() >= rect.xmin()
               && p.x() <= rect.xmax()
               && p.y() >= rect.ymin()
               && p.y() <= rect.ymax()) {

                set.add(p);
            }
        }

        return set;
    }

    // a nearest neighbor in the set to point p; null if the set is empty
    // O(N)
    public Point2D nearest(Point2D that) {

        double dist = Float.MAX_VALUE;
        Point2D nearest = null;
        for(Point2D p : tree) {
            if(p.distanceTo(that) < dist) {
                dist = p.distanceTo(that);
                nearest = p;
            }
        }

        return nearest;
    }

    // unit testing of the methods (optional)
    public static void main(String[] args) {

        StdDraw.setPenRadius(0.1);
        PointSET set = new PointSET();

        In in = new In("/home/adam/workspace/algorithms/coursera/algorithms/resources/kdtree/circle10.txt");
        double doubles[] = in.readAllDoubles();
        for(int i = 0; i < doubles.length; i += 2) {
            set.insert(new Point2D(doubles[i], doubles[i + 1]));
        }


        set.draw();
    }
}