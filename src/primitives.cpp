#include<math.h>
#include "primitives.h"
#include<limits>
#include<iostream>
#include<cmath>
#include<map>

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(coordinate x_in, coordinate y_in){
    x = x_in;
    y = y_in;
}

Point& Point::operator= (const Point& op){
    this->x = op.x;
    this->y = op.y;
}

bool Point::operator==(const Point &p2) {
    // TODO: Floating point errors handle? Some epsilon
    return this -> x == p2.x && this -> y == p2.y;
}

bool Point::operator!=(const Point &p2) {
    return this->x != p2.x || this->y != p2.y;
}

bool Point::operator< (const Point& right) const{
    if(x < right.x)
        return true;
    else if( x > right.x)
        return false;
    else
        return y < right.y;
}
//
//bool map<Point>::operator<(const Point p1, const Point p2){
//    if(p1.x < p2.x)
//        return true;
//    else if( p1,x > p2.x)
//        return false;
//    else
//        return p1.y < p2.y;
//}


bool Point::is_nan(){
    return(std::isnan(x) || std::isnan(y));
}

bool LineSegment::contains_point(Point pt) const{
    coordinate slope_diff = (pt.x - start_point.x) * (pt.y - end_point.y)
                          - (pt.x - end_point.x) * (pt.y - start_point.y);

    if(slope_diff != 0){
        return false;
    }
    else {
        if(start_point.x == end_point.x)
            return(pt.y <= end_point.y && pt.y >= start_point.y);
        else{
            coordinate t = (pt.x - start_point.x) / (end_point.x - start_point.x);
            return (t >= 0 && t <= 1);
        }
    }
}

Point LineSegment::intersects_at(LineSegment ls){
    Point p1 = this -> start_point,
          p2 = this -> end_point,
          p3 = ls.start_point,
          p4 = ls.end_point;

    coordinate denr = (p4.x - p3.x)*(p1.y - p2.y) - (p1.x - p2.x)*(p4.y - p3.y);
    
    if( denr == 0 ){
        return (NAN_POINT);
    }

    coordinate ta, tb;
    ta = (p3.y - p4.y)*(p1.x - p3.x) + (p4.x - p3.x)*(p1.y - p3.y);
    tb = (p1.y - p2.y)*(p1.x - p3.x) + (p2.x - p1.x)*(p1.y - p3.y);
    ta /= denr;
    tb /= denr;

    if(0 <= ta && ta <= 1 && 0 <= ta && ta <= 1){
        return Point(p1.x + ta * (p2.x - p1.x), p1.y + ta * (p2.y - p1.y));
    }
    else {
        return (NAN_POINT); 
    }

}

LineSegment::LineSegment(){
    this->start_point = NAN_POINT;
    this->end_point = NAN_POINT;
}

LineSegment::LineSegment(Point p1, Point p2){
    if(p1.x < p2.x){
        start_point = p1;
        end_point = p2;
    } else if (p1.x == p2.x && p1.y < p2.y) {
        start_point = p1;
        end_point = p2;
    } else {
        start_point = p2;
        end_point = p1;
    }
}


bool LineSegment::operator==(const LineSegment &l2) {
    return (this->start_point == l2.start_point && this->end_point == l2.end_point);
}

std::ostream& operator<<(std::ostream& os, const Point& pt){
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

Point LineSegment::start_pt() const{
    return(start_point);
}

Point LineSegment::end_pt() const {
    return(end_point);
}

Point LineSegment::y_projection(Point pt) const{
    if(end_point.y == start_point.y){
        return NAN_POINT;
    }
    else {
        coordinate x_coord = (pt.y - start_point.y) / (end_point.y - start_point.y);
        x_coord *= (end_point.x - start_point.x);
        x_coord += start_point.x;
        Point retPt = Point(x_coord, pt.y);
        return this -> contains_point(retPt) ? retPt : NAN_POINT ;
    }
}

std::ostream& operator<<(std::ostream& os, const LineSegment& l){
    os << "[" << l.start_point << ", " << l.end_point << "]";
    return os;
}


bool LineSegment::is_nan(){
    return(start_point.is_nan() || end_point.is_nan());
}
