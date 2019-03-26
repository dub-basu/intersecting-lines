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

////===============



    Point p1(-5,-5), p2(5,5);
    LineSegment l1(p1,p2);

    Point p3(-4,4), p4(6,-6);
    LineSegment l2(p3,p4);

    Point p5(0,10), p6(0,1);
    LineSegment l3(p5,p6);

    Point i = l1.intersects_at(l2);
    cout << i.x << " " << i.y << "\n";
    cout << i.is_nan();
    vector<LineSegment> inp {l1,l2,l3};
//
//    LineSegmentIntersector lsi(inp);
//
//    LSIResult res = lsi.computeIntersections();
//    cout<<res.size()<<endl;
//    //cout << res.begin() -> first.x << " " << res.begin() -> first.y << endl;
//    for (auto it : res){
//        cout << "Point : (" << it.first.x << " ," << it.first.y << ")\n";
////        cout<<"Segments-{";
////        for (it_seg : it.second)
////        {
////            cout<<
////        }
//    }

    return 0;
}
