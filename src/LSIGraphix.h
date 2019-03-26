#ifndef LSIGRAPHIX
#define LSIGRAPHIX

#define SWEEP_LINE_COLOR 0.0, 1.0, 1.0

#include "graphix.h"
#include "primitives.h"

class LSIGraphix: public Graphix {
    private:
        std::vector<LineSegment> input_lines;
        Point event_pt;
        LineSegment sweep_line;
        void draw_init_lines();
        void shift_sweep_line(Point);
    public:
        LSIGraphix(std::mutex& mtx);
        void init_lines(std::vector<LineSegment> lines);
        void update_event(Point);
        void draw_sweep_line();
};

#endif