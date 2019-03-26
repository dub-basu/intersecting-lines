#include<iostream>
//#include "D:\Studies\my repo\intersecting-lines\include\intersecting-lines\components.h"

#include "primitives.h"
#include "EventQueue.h"
#include "LineSegmentIntersector.h"
#include "Status.h"
using namespace std;

int main(){
//     Status<int> s;
//     s.insert(100);
//     s.insert(101);
//     s.insert(102);
//     s.insert(103);
//     s.insert(104);
//     s.insert(1);
//     s.insert(2);
//     s.insert(3);
//     s.insert(4);
//     s.insert(5);
//     s.insert(6);
//     s.inorder();
//
//     s.remove(1);
//     s.inorder();
//     cout << *(s.searchR(1));

    Point p1(1,1), p2(3,3);
    Point p3(2,1), p4(1,2);
    LineSegment l1(p1,p2);
    LineSegment l2(p3,p4);
//
    vector<LineSegment> inp {l1,l2};

    LineSegmentIntersector lsi(inp);

    LSIResult res = lsi.computeIntersections();
    cout << res.begin() -> first.x << " " << res.begin() -> first.y << endl;


    return 0;
}
