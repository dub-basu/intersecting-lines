#include<intersecting-lines/components.h>
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

    Point p_1(-50,-50);
    Point p_2(50,50);

    vector<LineSegment> lines;

    for(int i=0;i<10;i++){
        LineSegment l(p_1,p_2);
        p_1.x += 10;
        p_2.x -= 10;
        lines.push_back(l);
    }

    cout << endl;
    cout << endl;
    for(int i=0;i<lines.size();i++){
        cout << "start: (" << lines[i].start_pt().x << "," << lines[i].start_pt().y << ") | end point: (";
        cout << lines[i].end_pt().x << "," << lines[i].end_pt().y << ")" << endl;
    }

    gfx.init_lines(lines);
    gfx.render();

    Point p_new(12,5);
    gfx.update_event(p_new);
    gfx.render();

    p_new.y = 3;
    gfx.update_event(p_new);
    gfx.render();

    p_new.y = 0;;
    gfx.update_event(p_new);
    gfx.render();

    p_new.y = -6;
    gfx.update_event(p_new);
    gfx.render();

    t1.join();

//    Point pt1(23,11);
//    Point pt2(1,45);
//    cout << pt1.x << " " << pt1.y << endl;
//
//    LineSegment l1(pt2, pt1);
//    cout << l1.start_pt().x << " " << l1.start_pt().y << endl;
//    cout << l1.end_pt().x << " " << l1.end_pt().y;
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

//     Point p1(1,1), p2(3,3);
//     Point p3(2,1), p4(1,2);
//     LineSegment l1(p1,p2);
//     LineSegment l2(p3,p4);
// //
//     vector<LineSegment> inp {l1,l2};

//     LineSegmentIntersector lsi(inp);

//     LSIResult res = lsi.computeIntersections();
//     cout << res.begin() -> first.x << " " << res.begin() -> first.y << endl;


    return 0;
}
