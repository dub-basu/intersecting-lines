#ifndef INTERSECTING_LINES_LINESEGMENTINTERSECTOR_H
#define INTERSECTING_LINES_LINESEGMENTINTERSECTOR_H

#include <vector>
#include <set>
#include <map>
#include <list>
#include "EventQueue.h"
#include "primitives.h"
#include "Status.h"
#include "LSIGraphix.h"

typedef std::map< Point, std::list<LineSegment> > LSIResult;

class LineSegmentIntersector {
private:
    enum EventType {UPPER,LOWER,CONTAINING};

    class LSISegment {
    private:
    public:
        //LineSegmentIntersector& LSI;
        bool operator< (const LSISegment&) const;
        bool operator> (const LSISegment&) const;
        bool operator != (const LSISegment&) const;
        bool operator <= (const LSISegment&) const;
        LineSegment ls;
        LSISegment();
        LSISegment(LineSegment);
        LSISegment& operator=(LSISegment& );
        friend std::ostream& operator<<(std::ostream& os, const LSISegment& lsiSegment);
        bool operator==(LSISegment& );
    };


    // Internal Representation
    class LSIPoint {
    private:
    public:
        //LineSegmentIntersector& LSI;
        Point p;
        LSISegment lsiSegment;
        EventType et;
        bool operator< (LSIPoint);
        LSIPoint& operator= (LSIPoint&);
        LSIPoint(Point, LSISegment, EventType);
    };

    friend std::ostream& operator<<(std::ostream& os, const LSISegment& lsiSegment);

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
    LSIGraphix& lsiGfx;
    static Point lastReference;
    LineSegmentIntersector(std::vector<LineSegment>& , LSIGraphix&);
    LSIResult computeIntersections();

};


#endif //INTERSECTING_LINES_LINESEGMENTINTERSECTOR_H
