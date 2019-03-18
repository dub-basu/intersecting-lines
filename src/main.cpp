#include<iostream>
#include "D:\Studies\my repo\intersecting-lines\include\intersecting-lines\components.h"

#include "primitives.h"

using namespace std;

int main(){
    Point pt1(23,11);
    Point pt2(1,45);
    cout << pt1.x << " " << pt1.y << endl;

    LineSegment l1(pt2, pt1);
    cout << l1.start_pt().x << " " << l1.start_pt().y << endl;
    cout << l1.end_pt().x << " " << l1.end_pt().y;

    return 0;
}
