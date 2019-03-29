#ifndef LSIGRAPHIX
#define LSIGRAPHIX

#define SWEEP_LINE_COLOR 0.0, 1.0, 1.0

#include<vector>
#include "graphix.h"
#include "primitives.h"

/**
 * \class LSIGraphix
 * \brief Class for especially handling events for Bentley-Ottoman Algorithm.
 * Inherits Graphix class.
 */
class LSIGraphix: public Graphix {
    private:
        
        /**
        * Array of input lines. 
        */
        std::vector<LineSegment> input_lines;

        /**
        * Current event point to be highlighted. 
        */
        Point event_pt;

        /**
        * Current sweep line to be highlighted. 
        */
        LineSegment sweep_line;

        void draw_init_lines();
        void shift_sweep_line(Point);
        void draw_sweep_line();
        void draw_event_point();
    public:
        /**
        * Constructor. Calls super class Graphix constructor 
        * by passing mutex object and initiates a sweep line. 
        */
        LSIGraphix(std::mutex& mtx);

        /**
        * Updates list of input lines to be drawn.
        * @param lines updated set of lines
        */
        void init_lines(std::vector<LineSegment> lines);

        /**
        * Updates event point and sweep line in the window buffer.
        * @param Point New event point.
        */
        void update_event(Point);
};

#endif