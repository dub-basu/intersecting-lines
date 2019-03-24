#include<intersecting-lines/components.h>
#include<iostream>
#include<vector>
#include<thread>
#include <mutex>
#include "graphix.h"
#include "primitives.h"

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

    return(0);
}
