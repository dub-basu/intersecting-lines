#ifndef INTERSECTING_LINES_LINESEGMENTINTERSECTOR_H
#define INTERSECTING_LINES_LINESEGMENTINTERSECTOR_H

#include <vector>
#include <set>
#include <map>
#include <list>
#include "EventQueue.h"
#include "primitives.h"
#include "Status.h"
// #include "LSIGraphix.h"

/**
 * \class
 * LSI Result is the class that is returned by LineSegmentIntersector
 * It is a map of the intersection points to the list of line segments containing it
 */
typedef std::map< Point, std::list<LineSegment> > LSIResult;

/**
 * \class
 * This class encapsulates computations and visualisation of the event points
 */
class LineSegmentIntersector {
protected:
    enum EventType {UPPER,LOWER,CONTAINING};

    /**
     * \class
     * \brief Specializes primitive LineSegment class to suit algorithm requirements
     */
    class LSISegment: public LineSegment{
        private:
        public:
            bool operator< (const LSISegment&) const;
            bool operator> (const LSISegment&) const;
            bool operator != (const LSISegment&) const;
            bool operator <= (const LSISegment&) const;
            LSISegment();
            LSISegment(LineSegment);
            LSISegment& operator=(LSISegment& );
    };

    // Internal Representation
    /**
     * \class
     * \brief Specializes primitive Point class to suit algorithm requirements
     */
    class LSIPoint: public Point {
    private:
    public:
        //LineSegmentIntersector& LSI;
        LSISegment lsiSegment;
        EventType et;
        bool operator< (LSIPoint);
        LSIPoint& operator= (LSIPoint&);
        LSIPoint(Point, LSISegment, EventType);
    };

    LSIResult result;
    std::set<LSISegment> upper;
    std::set<LSISegment> lower;
    std::set<LSISegment> containing;
    Status<LSISegment> status;

    std::vector<LineSegment> &input;

    friend void swap(LSIPoint&, LSIPoint&);

    EventQueue<LineSegmentIntersector::LSIPoint> eventQueue;

    void handleEventPoint(Point);

    void findNewEvent(LSISegment*, LSISegment*, Point);

public:
    // LSIGraphix& lsiGfx;
    static Point lastReference;
    /**
     * Pass the set of points and LSI Visualizer Object
     *
     */
    LineSegmentIntersector(std::vector<LineSegment>&);

    /**
     * This computes the intersection point and visualizes it.
     * @return intersection points and all points that pass though it
     */
    LSIResult computeIntersections();

};

#endif
