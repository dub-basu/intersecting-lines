#include "LSIGraphix.h"

LSIGraphix::LSIGraphix(std::mutex& mtx):Graphix(mtx){
    Point start(-WIN_BREADTH / 2, WIN_HEIGHT);
    Point end(WIN_BREADTH / 2, WIN_HEIGHT);
    
    LineSegment temp(start, end);
    this -> sweep_line = temp;
}

void LSIGraphix::init_lines(std::vector<LineSegment> lines){
    this -> input_lines = lines;
    draw_init_lines();

    std::cout << sweep_line.start_pt().x << " " << sweep_line.start_pt().y << std::endl;
    std::cout << sweep_line.end_pt().x << " " << sweep_line.end_pt().y << std::endl;
    
    draw_sweep_line();
}

void LSIGraphix::draw_init_lines(){
    for(auto i: input_lines){
        Graphix::draw_line(i);
    }
}

void LSIGraphix::draw_sweep_line(){
    // glColor3f(SWEEP_LINE_COLOR);
    Graphix::draw_line(this -> sweep_line);
    // glColor3f(DRAW_COLOR);
}

void LSIGraphix::shift_sweep_line(Point pt){
    coordinate x_start_value = sweep_line.start_pt().x;
    coordinate x_end_value = sweep_line.end_pt().x;
    coordinate y_value = pt.y;

    Point start(x_start_value, y_value);
    Point end(x_end_value, y_value);
    LineSegment temp(start, end);

    sweep_line = temp;
}


void LSIGraphix::update_event(Point pt){
    this -> event_pt = pt;    
    shift_sweep_line(pt);

    Graphix::clear();
    draw_init_lines();
    draw_sweep_line();
    // draw_event_point();
}
