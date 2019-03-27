#include "LineSegmentIntersector.h"
#include "EventQueue.h"
#include "primitives.h"
#include<iostream>

using namespace std;

#define DELTA 0.00000001

void swap(LineSegmentIntersector::LSIPoint& p1, LineSegmentIntersector::LSIPoint& p2){
    //temp = p1
    LineSegmentIntersector::LSIPoint temp(p1.p, p1.lsiSegment, p1.et);
    //temp.lsiSegment = p1.lsiSegment;
    //temp.p = p1.p;
    //temp.et = p1.et;

    // p1 = p2
    p1.lsiSegment = p2.lsiSegment;
    p1.p = p2.p;
    p1.et = p2.et;

    // p2 = temp
    p2.lsiSegment = temp.lsiSegment;
    p2.p = temp.p;
    p2.et = temp.et;
}

Point LineSegmentIntersector::lastReference = NAN_POINT;

LineSegmentIntersector::LSISegment& LineSegmentIntersector::LSISegment::operator=(LineSegmentIntersector::LSISegment& a) {

//    std::cout << ".......\n\n\ncall hua \n\n\n...." << std::endl;
//    std::cout << "a point " << a.ls.start_pt().x << " " << a.ls.end_pt().y << std::endl;

    if(a.ls.start_pt().is_nan() || a.ls.end_pt().is_nan()) return(a);
    this->ls = a.ls;
    return *this;
}

LineSegmentIntersector::LSIPoint::LSIPoint( Point p,
                                            LineSegmentIntersector::LSISegment lsis,
                                            LineSegmentIntersector::EventType et
                                           ){
    this->p = p;
    this->lsiSegment = lsis;
    this->et = et;
}


bool LineSegmentIntersector::LSIPoint::operator<(LineSegmentIntersector::LSIPoint lsip2) {
    Point p1 = this->p;
    Point p2 = lsip2.p;

    if (p1.y < p2.y){
        return false;
    }
    else if (p1.y == p2.y){
        return p1.x < p2.x;
    }
    else{
        return true;
    }

}

LineSegmentIntersector::LSIPoint& LineSegmentIntersector::LSIPoint::operator= (LSIPoint& lp){
    this -> p = lp.p;
    this -> lsiSegment = lp.lsiSegment;
    this -> et = lp.et;
}

bool LineSegmentIntersector::LSISegment::operator==(LineSegmentIntersector::LSISegment& lsiSegment){
    return(this -> ls == lsiSegment.ls);
}

LineSegmentIntersector::LSISegment::LSISegment(){
    this->ls = NAN_LINE;
}

LineSegmentIntersector::LSISegment::LSISegment(LineSegment l){
    //std::cout << "lsi segment const called \n" ;
    this->ls = l;
}


/* PENDING */
bool LineSegmentIntersector::LSISegment::operator<(const LineSegmentIntersector::LSISegment& lsi) const {
    return this->ls.y_projection(LineSegmentIntersector::lastReference).x
                    < lsi.ls.y_projection(LineSegmentIntersector::lastReference).x;
}

bool LineSegmentIntersector::LSISegment::operator>(const LineSegmentIntersector::LSISegment& lsi) const {
    return this->ls.y_projection(LineSegmentIntersector::lastReference).x
           > lsi.ls.y_projection(LineSegmentIntersector::lastReference).x;
}

bool LineSegmentIntersector::LSISegment::operator !=(const LineSegmentIntersector::LSISegment& lsi) const {
    return this->ls.y_projection(LineSegmentIntersector::lastReference).x
           != lsi.ls.y_projection(LineSegmentIntersector::lastReference).x;
}

bool LineSegmentIntersector::LSISegment::operator <=(const LineSegmentIntersector::LSISegment& lsi) const {
    return this->ls.y_projection(LineSegmentIntersector::lastReference)
           < lsi.ls.y_projection(LineSegmentIntersector::lastReference);
}
///////////////////////////////////



LineSegmentIntersector::LineSegmentIntersector(std::vector<LineSegment> &i, LSIGraphix& gfx) : input(i), lsiGfx(gfx){
    lsiGfx.init_lines(i);
    for (auto it : input){
        LSISegment lsi_it(it);
        Point p1 = it.start_pt();
        Point p2 = it.end_pt();
        cout << eventQueue.size();
        EventType p1Type, p2Type;

        if(p1.y > p2.y ){
            // P1 is upper;
            p1Type = UPPER;
            p2Type = LOWER;
        }
        else if(p1.y == p2.y){
            if(p1.x < p2.x){
                // P1 is upper
                p1Type = UPPER;
                p2Type = LOWER;
            }
            else{
                //P2 is upper
                p1Type = LOWER;
                p2Type = UPPER;
            }
        }
        else{
            // P2 is upper
            p1Type = LOWER;
            p2Type = UPPER;
        }

        LSIPoint lsip1(p1,lsi_it,p1Type);
        LSIPoint lsip2(p2,lsi_it,p2Type);

        eventQueue.insert(lsip1);
        eventQueue.insert(lsip2);
    }

    lastReference = eventQueue.peek().p;

}

LSIResult LineSegmentIntersector::computeIntersections() {
    while(eventQueue.size() > 0){
        upper.clear();
        lower.clear();
        containing.clear();

        std::cout << "event queue size = " << eventQueue.size() << std::endl;

        Point curr = eventQueue.peek().p;
        lsiGfx.update_event(curr);
        handleEventPoint(curr);
        lsiGfx.render();
    }

    return result;

}

void LineSegmentIntersector::handleEventPoint(Point curr) {
    LSISegment* lastContaining = nullptr;

    while(eventQueue.size() > 0 && eventQueue.peek().p == curr){

        std::cout << "curr = " << curr.x << " " << curr.y << std::endl;

        LSIPoint toInsert = eventQueue.extractMin();
        if(toInsert.et ==  UPPER){
            //std::cout << "printy boi" << std::endl;
            upper.insert(toInsert.lsiSegment);
        }
        else if(toInsert.et == LOWER){
            lower.insert(toInsert.lsiSegment);
            //status.remove(toInsert.lsiSegment);
        }
        else if (toInsert.et == CONTAINING){
            containing.insert(toInsert.lsiSegment);
            lastContaining = &(toInsert.lsiSegment);
        }
        else{
            std::cout << "error\n";
        }

        if (containing.size() > 0){

            //std::cout << "containing size = " << containing.size() << std::endl;

            LSISegment* toAdd = lastContaining;
            while( toAdd != nullptr && (toAdd->ls.contains_point(curr))) {
                if (toAdd->ls.start_pt() != curr && toAdd->ls.end_pt() != curr){
                    containing.insert(*toAdd);
                }
                toAdd = status.searchL(*toAdd);

            }

            toAdd = lastContaining;
            while( toAdd != nullptr && toAdd->ls.contains_point(curr)) {
                if (toAdd->ls.start_pt() != curr && toAdd->ls.end_pt() != curr) {
                    containing.insert(*toAdd);
                }
                    toAdd = status.searchR(*toAdd);
            }
        }
//        std::cout << "eq here\n";
    }

    // For reordering efficiently

    if(upper.size() + lower.size() + containing.size() > 1){
        //result[curr] = list<LineSegment>();
        for (auto i : upper){
            result[curr].push_front(i.ls);
        }
        for (auto i : lower){
            result[curr].push_front(i.ls);
        }
        for (auto i : containing){
            result[curr].push_front(i.ls);
        }
    }

    for (auto i : lower){
        status.remove(i);
    }

    for (auto i : containing){
        status.remove(i);
    }

    // Ordering New parameter del line
    lastReference = Point(curr.x, curr.y - DELTA);

    set<LSISegment> uc;
    for (auto i : upper){
        uc.insert(i);
        status.insert(i);
    }
    for (auto i : containing){
        uc.insert(i);
        status.insert(i);
    }

    if (uc.size() == 0){
        // Fake vertical line insert in status;
        Point fakeLineLower = Point(curr.x, curr.y + DELTA);
        LineSegment fakeLineSegment(curr,fakeLineLower);
        LSISegment fakeLSISegment(fakeLineSegment);
        // Get left and right neighbors;
        status.insert(fakeLSISegment);
        LSISegment* sl = status.searchL(fakeLSISegment);
        LSISegment* sr = status.searchR(fakeLSISegment);

        status.remove(fakeLSISegment);

        findNewEvent(sl,sr,curr);


    }
    else{
        LSISegment sl = *(uc.begin());
        LSISegment sr = *(--uc.end());

        LSISegment* sll = status.searchL(sl);
        LSISegment* srr = status.searchR(sr);

        findNewEvent(sll,&sl,curr);
        findNewEvent(srr,&sr,curr);

    }
}

void LineSegmentIntersector::findNewEvent(LSISegment* sl, LSISegment* sr, Point pt){
    if(sl == NULL || sr == NULL) return;
    else{
        Point intersectionPoint = (sl->ls).intersects_at(sr->ls);
        if (intersectionPoint.is_nan()) return;
        else{
            if( intersectionPoint.y < pt.y ||
                (intersectionPoint.y == pt.y && intersectionPoint.x > pt.x)){
                LSIPoint toAdd(intersectionPoint, *sl, LineSegmentIntersector::CONTAINING);
                eventQueue.insert(toAdd);
            }
        }
    }
}