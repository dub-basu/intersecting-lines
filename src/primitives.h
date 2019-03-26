#ifndef PRIMITIVES
#define PRIMITIVES

#include<iostream>
#include<cmath>
#include<limits>

typedef long double coordinate;
typedef long double len;

#define NAN_POINT Point(std::numeric_limits<coordinate>::quiet_NaN(), \
                        std::numeric_limits<coordinate>::quiet_NaN())
#define NAN_LINE LineSegment(NAN_POINT, NAN_POINT)

class Point{
    public:
        coordinate x;
        coordinate y;
        Point();
        Point(coordinate x_in, coordinate y_in);
        bool operator== (const Point& p2);
        bool operator!= (const Point& p2);
        bool is_nan();
        bool operator< (const Point& right) const;
//        bool map<Point> operator<(const Point, const Point);
};

class LineSegment{
    private:
        Point start_point;
        Point end_point;
    public:
        LineSegment();
        LineSegment(Point p1, Point p2);
        bool contains_point(Point pt) const;
        Point intersects_at(LineSegment ls);
        Point y_projection(Point pt) const;
        bool operator== (const LineSegment& l2);
        //len length();
        Point start_pt();
        Point end_pt();
};

#endif
