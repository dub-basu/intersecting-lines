#include "LineSegmentIntersector.h"
#include "EventQueue.h"
#include "primitives.h"
#include<iostream>

using namespace std;

#define DELTA 0.5

void swap(LineSegmentIntersector::LSIPoint& p1, LineSegmentIntersector::LSIPoint& p2){
    LineSegmentIntersector::LSIPoint temp(p1.p, p1.lsiSegment, p1.et);

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
    if(a.ls.start_pt().is_nan() || a.ls.end_pt().is_nan()) return(a);
    this->ls = a.ls;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const LineSegmentIntersector::LSISegment& lsiSegment){
    os << lsiSegment.ls;
    return os;
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
    Point this_upper = this->ls.start_pt(), this_lower = this->ls.end_pt();
    Point lsi_upper = lsi.ls.start_pt(), lsi_lower = lsi.ls.end_pt();

    const LSISegment debug = LSISegment(LineSegment(Point(1,9),Point(3,8)));

    if((this_upper.y < this_lower.y) || (this_upper.y == this_lower.y && this_upper.x >= this_lower.x)){
        Point temp = this_upper;
        this_upper = this_lower;
        this_lower = temp;
    }
    if((lsi_upper.y < lsi_lower.y) || (lsi_upper.y == lsi_lower.y && lsi_upper.x >= lsi_lower.x)){
        Point temp = lsi_upper;
        lsi_upper = lsi_lower;
        lsi_lower = temp;
    }

    if ((lastReference == this_upper || lastReference == this_lower) &&
        (lastReference == lsi_upper  || lastReference == lsi_lower) ){

        if (lastReference == this_upper && lastReference == lsi_upper){
            Point comp = Point(lastReference.x, lastReference.y - DELTA);

            bool toReturn = this->ls.y_projection(comp).x
                   < lsi.ls.y_projection(comp).x;
            return toReturn;
        }
        if (lastReference == this_upper && lastReference == lsi_lower){
//            cout << true << "\n";
            return true;
        }
        if (lastReference == this_lower && lastReference == lsi_lower){
//            cout << "LL\n";
            Point comp = Point(lastReference.x, lastReference.y + DELTA);

            bool toReturn = this->ls.y_projection(comp).x
                   < lsi.ls.y_projection(comp).x;
//            cout << toReturn << "\n";
            return toReturn;
        }
        if (lastReference == this_lower && lastReference == lsi_upper){
//            cout << false << "\n";
            return false;
        }

    }
    else if(lastReference == this_lower || lastReference == lsi_lower){
        Point comp = Point(lastReference.x, lastReference.y + DELTA);
        bool toReturn = this->ls.y_projection(comp).x
               < lsi.ls.y_projection(comp).x;
        return toReturn;
    }
    else  {

        // Only in case of ordering event point
        Point comp = Point(lastReference.x, lastReference.y - DELTA);
        bool toReturn = this->ls.y_projection(comp).x
                        < lsi.ls.y_projection(comp).x;
        return toReturn;
    }
}

bool LineSegmentIntersector::LSISegment::operator>(const LineSegmentIntersector::LSISegment& lsi) const {
     return !(*this < lsi) && (lsi < *this);
}

bool LineSegmentIntersector::LSISegment::operator !=(const LineSegmentIntersector::LSISegment& lsi) const {
    return *this < lsi || lsi < *this;
}

bool LineSegmentIntersector::LSISegment::operator <=(const LineSegmentIntersector::LSISegment& lsi) const {
    return !(lsi < *this);
}
///////////////////////////////////


LineSegmentIntersector::LineSegmentIntersector(std::vector<LineSegment> &i, LSIGraphix& l) 
                                : input(i), lsiGfx(l){
    lsiGfx.init_lines(i);
    for (auto it : input){
        LSISegment lsi_it(it);
        Point p1 = it.start_pt();
        Point p2 = it.end_pt();
        //cout << eventQueue.size();
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

        //std::cout << "event queue size = " << eventQueue.size() << std::endl;

        Point curr = eventQueue.peek().p;
        lsiGfx.update_event(curr);
        handleEventPoint(curr);
        lsiGfx.render();
    }

    return result;

}

void LineSegmentIntersector::handleEventPoint(Point curr) {
    cout << curr << "\n";
    LSISegment* lastContaining = NULL;
    Point temp = lastReference;
    lastReference = curr;
    while(eventQueue.size() > 0 && eventQueue.peek().p == curr) {
        LSIPoint toInsert = eventQueue.extractMin();
        if (toInsert.et == UPPER) {
            upper.insert(toInsert.lsiSegment);
            cout << "\t" << toInsert.lsiSegment.ls;
            cout << "UPPER SIZE = " << upper.size() << "\n";
        } else if (toInsert.et == LOWER) {
            lower.insert(toInsert.lsiSegment);
            cout << "\t" << toInsert.lsiSegment.ls;
            cout << "LOWER SIZE = " << lower.size() << "\n";
        } else if (toInsert.et == CONTAINING) {
            LineSegment candidate = toInsert.lsiSegment.ls;
            if(curr != candidate.start_pt() && curr != candidate.end_pt()) {
                containing.insert(toInsert.lsiSegment);
                cout << "\t" << toInsert.lsiSegment.ls;
                lastContaining = &(toInsert.lsiSegment);
                cout << "CONTAINING SIZE = " << containing.size() << "\n";
            }
        } else {
            std::cout << "error\n";
        }
    }

    if (containing.size() > 0){
        //std::cout << "containing size = " << containing.size() << std::endl;

        LSISegment* toAdd = lastContaining;
        while( toAdd != NULL && (toAdd->ls.contains_point(curr))) {
        //    cout << "L";
        //    if (toAdd->ls.start_pt() != curr && toAdd->ls.end_pt() != curr){
                containing.insert(*toAdd);
         //   }
            toAdd = status.searchL(*toAdd);
        }

        toAdd = lastContaining;
        while( toAdd != NULL && toAdd->ls.contains_point(curr)) {
            //   cout << "R";
            // if (toAdd->ls.start_pt() != curr && toAdd->ls.end_pt() != curr) {
                containing.insert(*toAdd);
            // }
            toAdd = status.searchR(*toAdd);
        }

        cout << "\tFINAL CONTAINING " << containing.size() << "\n";
    }

    // For reordering efficiently
    lastReference = temp;
    for (auto i : lower){
        status.remove(i);
    }

    for (auto i : containing){
        status.remove(i);
    }

    lastReference = curr;
    set<LSISegment> luc;

    for (auto i : upper) {
//        cout << i.ls << "\n";
        luc.insert(i);
    }

//    cout << "\t LOWER= " << lower.size() << "\n";
    for (auto i : lower) {
//        cout << i.ls << "\n";
        cout << "\tRemoving : " << i.ls << "\n";
        luc.insert(i);
    }

    for (auto i : containing) {
//        cout << i.ls << "\n";
        luc.insert(i);
//        cout << "[CONTAINING] " << luc.size() << "\n";
    }

    if(luc.size() > 1){
        for (auto i : luc){
            result[curr].push_front(i.ls);
        }
    }

    // Ordering New parameter del line
    lastReference = curr;

    set<LSISegment> uc;
    for (auto i : upper){
        uc.insert(i);
        cout << "\tInserting : " << i.ls << "\n";
        status.insert(i);
    }
    for (auto i : containing){
        uc.insert(i);
        cout << "\tReinserting : " << i.ls << "\n";
        status.insert(i);
    }

    cout << "\tStatus ";
    status.inorder();
    cout << "\n\t===================================\n";


    if (uc.size() == 0){
        // Fake vertical line insert in status;
        //cout << "Test1\n";
        Point fakeLineLower = Point(curr.x, curr.y - DELTA);
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
                LSIPoint toAdd2(intersectionPoint, *sr, LineSegmentIntersector::CONTAINING);
                eventQueue.insert(toAdd);
                eventQueue.insert(toAdd2);
            }
        }
    }
}