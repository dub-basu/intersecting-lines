#include<iostream>
//#include "D:\Studies\my repo\intersecting-lines\include\intersecting-lines\components.h"

//#include "primitives.h"
#include "Status.cpp"
#include "EventQueue.cpp"
using namespace std;

int main(){
//    Point pt1(23,11);
//    Point pt2(1,45);
//    cout << pt1.x << " " << pt1.y << endl;
//
//    LineSegment l1(pt2, pt1);
//    cout << l1.start_pt().x << " " << l1.start_pt().y << endl;
//    cout << l1.end_pt().x << " " << l1.end_pt().y;
    Status<int> s;
    s.insert(100);
    s.insert(101);
    s.insert(102);
    s.insert(103);
    s.insert(104);
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.inorder();

    s.remove(1);
    s.inorder();
    cout << *(s.searchR(1));

    return 0;
}
