#include<math.h>
#include "primitives.h"
#include<limits>
#include<iostream>
#include<cmath>

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(coordinate x_in, coordinate y_in){
    x = x_in;
    y = y_in;
}

bool Point::operator==(const Point &p2) {
    // TODO: Floating point errors handle? Some epsilon
    return this -> x == p2.x && this -> y == p2.y;
}

bool Point::is_nan(){
    return(std::isnan(x) || std::isnan(y));
}

bool LineSegment::contains_point(Point pt){
    coordinate slope_diff = (pt.x - start_point.x) * (pt.y - start_point.y)
                          - (pt.x - end_point.x) * (pt.y - end_point.y);

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
    std::cout << denr << std::endl;
    
    if( denr == 0 ){
        return Point(   std::numeric_limits<coordinate>::quiet_NaN(), 
                        std::numeric_limits<coordinate>::quiet_NaN());
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
        return Point(   std::numeric_limits<coordinate>::quiet_NaN(), 
                        std::numeric_limits<coordinate>::quiet_NaN()); 
    }

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

Point LineSegment::start_pt(){
    return(start_point);
}

Point LineSegment::end_pt(){
    return(end_point);
}

len LineSegment::length(){
    len l = pow((end_point.y - start_point.y), 2) + 
            pow((end_point.x - start_point.x), 2);
    l = sqrt(l);
    return(l);
}

// TODO: Implement the rest of the functions of LineSegment class
