#include "primitives.h"

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(coordinate x_in, coordinate y_in){
    x = x_in;
    y = y_in;
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

// TODO: Implement the rest of the functions of LineSegment class
