#ifndef PRIMITIVES
#define PRIMITIVES

typedef long double coordinate;
typedef long double len;

class Point{
    public:
        coordinate x;
        coordinate y;
        Point();
        Point(coordinate x_in, coordinate y_in);
        bool operator< (const Point &right);
};

class LineSegment{
    private:
        Point start_point;
        Point end_point;
    public:
        LineSegment(Point p1, Point p2);
        bool contains_point(Point pt);
        bool intersects_with(LineSegment ls);
        len length();  
        Point start_pt();
        Point end_pt();
};

#endif
