#include<intersecting-lines/components.h>
#include<iostream>
#include<vector>
#include<thread>
#include <mutex>
#include "graphix.h"
#include "primitives.h"

#include "primitives.h"
#include "Status.cpp"
#include "EventQueue.cpp"
using namespace std;

void init_graphix_class(Graphix* x){
    x->loopie();
}

int main(int argc, char** argv){

    std::mutex mtx;
    Graphix gfx(mtx);
    thread t1(init_graphix_class, &gfx);

    Point p1(-50,-50);
    Point p2(50,50);

    vector<LineSegment> lines;

    for(int i=0;i<10;i++){
        LineSegment l(p1,p2);
        p1.x += 10;
        p2.x -= 10;
        lines.push_back(l);
    }

    cout << endl;
    cout << endl;
    for(int i=0;i<lines.size();i++){
        cout << "start: (" << lines[i].start_pt().x << "," << lines[i].start_pt().y << ") | end point: (";
        cout << lines[i].end_pt().x << "," << lines[i].end_pt().y << ")" << endl;
        gfx.draw_line(lines[i]);
        gfx.render();    
    }

    t1.join();

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

    Point p1(1,1), p2(3,3);
    Point p3(2,1), p4(4,3);
    LineSegment l1(p1,p2);
    LineSegment l2(p3,p4);
    
    Point p5;
    p5 = l2.intersects_at(l1);
    cout << p5.is_nan();
    // cout << p5.x << " " << p5.y << endl;
    // Point p6(1,-30);
    // if(l1.contains_point(p6)) cout << "true" << endl;
    // else cout << "false" << endl;

    return(0);
}
