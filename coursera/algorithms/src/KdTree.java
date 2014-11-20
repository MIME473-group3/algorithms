import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class KdTree {

    private static class Node {
        Point2D point;
        Node left;
        Node right;
        Node parent;
        RectHV rect;

        Node(Point2D point) {
            this.point = point;
            left = null;
            right = null;
            parent = null;
            rect = null;
        }
    }

    private Node root;
    private int size;

    // construct an empty set of points
    public KdTree() {
        size = 0;
        root = null;
    }

    // is the set empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // number of points in the set
    public int size() {
        return size;
    }
    
    private boolean insert(Node root, Point2D p, boolean isX) {

        if(root.point.equals(p)) {
            return false;
        }

        if(isX) {
            
            if(root.point.x() > p.x()) {
                if(root.left != null) {
                    return insert(root.left, p, false);
                } else {
                    root.left = new Node(p);
                    root.left.parent = root;
                    root.left.rect = new RectHV(root.rect.xmin(), root.rect.ymin(), root.point.x(), root.rect.ymax());
                }
            } else {
                if(root.right != null) {
                    return insert(root.right, p, false);
                } else {
                    root.right = new Node(p);
                    root.right.parent = root;
                    root.right.rect = new RectHV(root.point.x(), root.rect.ymin(), root.rect.xmax(), root.rect.ymax());

                }
            }
            
        } else {

            if(root.point.y() > p.y()) {
                if(root.left != null) {
                    return insert(root.left, p, true);
                } else {
                    root.left = new Node(p);
                    root.left.parent = root;
                    root.left.rect = new RectHV(root.rect.xmin(), root.rect.ymin(), root.rect.xmax(), root.point.y());
                }
            } else {
                if(root.right != null) {
                    return insert(root.right, p, true);
                } else {
                    root.right = new Node(p);
                    root.right.parent = root;
                    root.right.rect = new RectHV(root.rect.xmin(), root.point.y(), root.rect.xmax(), root.rect.ymax());
                }
            }
            
        }
        return true;
    }

    private boolean insert(Node root, Point2D p) {
        return insert(root, p, true);
    }

    // add the point to the set (if it is not already in the set)
    // O(log(n))
    public void insert(Point2D p) {
        if(root == null) {
            root = new Node(p);
            root.rect = new RectHV(0, 0, 1, 1);
            size = 1;
            return;
        }

        if(insert(root, p)) {
            size += 1;
        }
    }

    private boolean contains(Node root, Point2D p, boolean isX) {

        if(root == null) {
            return false;
        }

        if(root.point.equals(p)) {
            return true;
        }

        if(isX) {
            if(root.point.x() > p.x())
                return contains(root.left, p, false);
            else {
                return contains(root.right, p, false);
            }

        } else {
            if(root.point.y() > p.y()) {
                return contains(root.left, p, true);
            } else {
                return contains(root.right, p, true);
            }
        }
    }

    private boolean contains(Node root, Point2D p) {
        return contains(root, p, true);
    }

    // does the set contain point p?
    // O(log(n))
    public boolean contains(Point2D p) {
        if(isEmpty()) {
            return false;
        }

        return contains(root, p);
    }

    private void draw(Node root, boolean isX) {
        if(root == null) {
            return;
        }

        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.setPenRadius(.01);
        root.point.draw();

        StdDraw.setPenRadius();
        if(isX) {
            StdDraw.setPenColor(StdDraw.RED);
            StdDraw.line(root.point.x(), root.rect.ymin(), root.point.x(), root.rect.ymax());
        } else {
            StdDraw.setPenColor(StdDraw.BLUE);
            StdDraw.line(root.rect.xmin(), root.point.y(), root.rect.xmax(), root.point.y());
        }

        draw(root.left, !isX);
        draw(root.right, !isX);
    }

    // draw all points to standard draw
    public void draw() {
        draw(root, true);
    }
    
    private void range(Node root, RectHV rect, Set<Point2D> set) {

        Point2D p = root.point;
        if(p.x() >= rect.xmin() && p.x() <= rect.xmax() && p.y() >= rect.ymin() && p.y() <= rect.ymax()) {
            set.add(p);
        }

        if(root.left != null && rect.intersects(root.left.rect)) {
            range(root.left, rect, set);
        }

        if(root.right != null && rect.intersects(root.right.rect)) {
            range(root.right, rect, set);
        }
    }

    // all points that are inside the rectangle
    // O(N)
    public Iterable<Point2D> range(RectHV rect) {

        HashSet<Point2D> set = new HashSet<Point2D>();
        if(isEmpty()) {
            return set;
        }

        range(root, rect, set);

        return set;
    }


    private Point2D nearest(Node root, Point2D p, double minimal, boolean isX) {
        
        if(!(root.rect.distanceSquaredTo(p) < minimal)) {
            return null;
        }

        Point2D nearest = null;
        double dist = root.point.distanceSquaredTo(p);
        if(dist < minimal) {
            minimal = dist;
            nearest = root.point;
        }

        if(isX) {

            if(p.x() < root.point.x()) {

                Point2D left = root.left != null ? nearest(root.left, p, minimal, false) : null;
                double leftDist = left != null ? left.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(leftDist < minimal) {
                    minimal = leftDist;
                    nearest = left;
                }

                Point2D right = root.right != null ? nearest(root.right, p, minimal, false) : null;
                double rightDist = right != null ? right.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(rightDist < minimal) {
                    nearest = right;
                }

            } else {

                Point2D right = root.right != null ? nearest(root.right, p, minimal, false) : null;
                double rightDist = right != null ? right.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(rightDist < minimal) {
                    minimal = rightDist;
                    nearest = right;
                }

                Point2D left = root.left != null ? nearest(root.left, p, minimal, false) : null;
                double leftDist = left != null ? left.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(leftDist < minimal) {
                    nearest = left;
                }

            }

        } else {

            if(p.y() < root.point.y()) {

                Point2D left = root.left != null ? nearest(root.left, p, minimal, true) : null;
                double leftDist = left != null ? left.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(leftDist < minimal) {
                    minimal = leftDist;
                    nearest = left;
                }

                Point2D right = root.right != null ? nearest(root.right, p, minimal, true) : null;
                double rightDist = right != null ? right.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(rightDist < minimal) {
                    nearest = right;
                }

            } else {

                Point2D right = root.right != null ? nearest(root.right, p, minimal, true) : null;
                double rightDist = right != null ? right.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(rightDist < minimal) {
                    minimal = rightDist;
                    nearest = right;
                }

                Point2D left = root.left != null ? nearest(root.left, p, minimal, true) : null;
                double leftDist = left != null ? left.distanceSquaredTo(p) : Double.MAX_VALUE;

                if(leftDist < minimal) {
                    nearest = left;
                }
            }
        }

        return nearest;
    }

    // a nearest neighbor in the set to point p; null if the set is empty
    // O(N)
    public Point2D nearest(Point2D that) {
        return nearest(root, that, Double.MAX_VALUE, true);
    }

    // unit testing of the methods (optional)
    public static void main(String[] args) {

        StdDraw.setPenRadius(0.05);
        KdTree set = new KdTree();

        In in = new In("/home/adam/workspace/algorithms/coursera/algorithms/resources/kdtree/circle10.txt");
        double doubles[] = in.readAllDoubles();
        for(int i = 0; i < doubles.length; i += 2) {
            set.insert(new Point2D(doubles[i], doubles[i + 1]));
        }

        for(int i = 0; i < doubles.length; i += 2) {
            System.out.println(set.contains(new Point2D(doubles[i], doubles[i + 1])));
        }

        for(Point2D p : set.range(new RectHV(0, 0, 0.6, 0.6))) {
            System.out.println(p);
        }


        set.draw();
    }
}