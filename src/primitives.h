#ifndef PRIMITIVES
#define PRIMITIVES

#include<iostream>
#include<cmath>
#include<limits>

typedef long double coordinate;
typedef long double len;

/**
 * NAN_POINT is null equivalent of a point
 *
 * Returned in case two lines are parallel,
 * and we try to compute intersection point
 */
#define NAN_POINT Point(std::numeric_limits<coordinate>::quiet_NaN(), \
                        std::numeric_limits<coordinate>::quiet_NaN())

/**
 * NAN_LINE is a LineSegment with endpoints as NAN_POINTs
 */
#define NAN_LINE LineSegment(NAN_POINT, NAN_POINT)



/**
 *  \class Point
 *
 *  \brief Stores point with X & Y coordinate
 *  \example Point p(3,5): p is point with coordinates (3,5)
 */
class Point{
private:
    friend std::ostream& operator<<(std::ostream& os, const Point& pt);

public:
        /**
         * the X coordinate of the point
         * can be accessed publicly
         */
        coordinate x;
        /**
         * the X coordinate of the point
         * can be accessed publicly
         */
        coordinate y;

        /**
         * Constructor, makes a point with x & y coordinates 0
         */
        Point();

        /**
         *
         * @param x_in : X coordinate of point
         * @param y_in : Y coordinate of point
         */
        Point(coordinate x_in, coordinate y_in);

        /**
         * Standard overloading the = operator
         * @param op
         * @return point with coordinates as that of input point
         */
        Point& operator= (const Point& op);

        /**
        * Two points are equal if they have same x & y coordinates
        * @param p2
        * @return true if the points are same
        */
        bool operator== (const Point& p2);

        /**
         * Overloaded != operator. Refer to = for point
         * @param p2 - Point to be compared with
         * @return true if points have at least one different coordinate
         */
        bool operator!= (const Point& p2);

        /**
         * This operator does not have any semantic meaning
         * A hard ordering of points has been done to ensure
         * Points can be inserted into STL containers
         * @param right
         * @return bool
         */
        bool operator< (const Point& right) const;

        /**
         * Checks if a point is a NAN_POINT
         * @return true if point is a NAN_POINT
         */
        bool is_nan();

//        bool map<Point> operator<(const Point, const Point);
};
/**
 * \class LineSegment
 * \brief Class for line segments
 *
 * There is an inherent ordering between the two
 * end points. So, initialising order in constructor
 * does not affect the behaviour of the object
 */
class LineSegment{
    private:
        Point start_point;
        Point end_point;
        friend std::ostream& operator<<(std::ostream& os, const LineSegment& l);
    public:
        /**
         *
         */
        LineSegment();
        /**
         * \brief Constructor, specifying two endpoints of the segment
         * @param p1 One endpoint of the line segment
         * @param p2 The other endpoint of the line segment
         */
        LineSegment(Point p1, Point p2);

        /**
         * This function checks if a point lies on
         * the given line segment. It returns true
         * even if the point is onr of the endpoints
         * of the line segment
         * @param pt Point to check
         * @return true if point lies on line
         */
        bool contains_point(Point pt) const;

        /**
         *
         * @param ls The line segment to check with
         * @return Point where the two line segments intersect
         * @return NAN_POINT if the segments dont intersect
         */
        Point intersects_at(LineSegment ls);

        /**
         * Returns a point that is a horizontal
         * projection of the parameter point
         * on the line segment. NAN_POINT returned
         * if no point found
         * @param pt Point whose horizontal projection we want to find
         * @return Point which is horizontal projection of the
         * @return NAN_POINT if no projection
         */
        Point horizontal_projection(Point pt) const;

        /**
         * Two lines are equal if they have the same
         * endpoints
         * @param l2
         * @return true if the two line segments are the same
         */
        bool operator== (const LineSegment& l2);
        //len length();

        /**
         * Returns start point of the line segment
         * Initialisation order does not matter
         * @return
         */
        Point start_pt() const ;

        /**
         * Returns end point of the line segment
         * Initialisation order does not matter
         * @return
         */
        Point end_pt() const ;

        /**
         *
         * @return true if line segment is NAN_LINE
         */
        bool is_nan();
};

#endif
