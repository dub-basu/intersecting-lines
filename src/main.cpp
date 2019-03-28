#include<iostream>
#include<vector>
#include<thread>
#include <mutex>
#include "graphix.h"
#include "primitives.h"
#include "EventQueue.h"
#include "LineSegmentIntersector.h"
#include "Status.h"
#include "LSIGraphix.h"
using namespace std;

void init_graphix_class(LSIGraphix* x){
    x->loopie();
}

int main(int argc, char** argv){

    std::mutex mtx;
    LSIGraphix gfx(mtx);
    thread t1(init_graphix_class, &gfx);

    Point p1(-5,-5), p2(5,5);
    LineSegment l1(p1,p2);

    Point p3(-4,4), p4(6,-6);
    LineSegment l2(p3,p4);

    Point p5(0,6), p6(0,1.5);
    LineSegment l3(p5,p6);

    Point p7(3,8), p8(3,-10);
    LineSegment l4(p7,p8);

    Point p9(0,1), p10(0,-5);
    LineSegment l5(p9,p10);

    //Point p11(1,9),p12(2,9),p13(4,10);
    Point p11(0,9.5),p12(2,9),p13(4,10);
    LineSegment l6(p7,p11), l7(p7,p12), l8(p7,p13);

    Point p14(1,5), p15(4,8);
    LineSegment l9(p14,p15);
//
    Point p16(1,6), p17(4,9);
    LineSegment l10(p16,p17);

    Point p18(1,-11),p19(2,-11);
    LineSegment l11(p18,p8), l12(p19,p8);

    Point p20(-3,3), p21(-4,2);
    LineSegment l13(p20,p21);

    vector<LineSegment> inp {l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13};
//    vector<LineSegment> inp {l1,l2};
    LineSegmentIntersector lsi(inp, gfx);

    LSIResult res = lsi.computeIntersections();
    cout << "RESULT:\n";
    //cout << res.size();

    for (auto i : res){
        cout << i.first << " : ";
        cout << i.second.size() << "\n";
        for (auto j : i.second){
            cout << "\t" << j << "\n";
        }
    }

    t1.join();
    return 0;
}
