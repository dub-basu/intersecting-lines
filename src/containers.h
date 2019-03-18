#ifndef CONTAINERS
#define CONTAINERS

#include<vector>
#include "primitives.h"

using namespace std;

class InputSet{
    private:
        vector<LineSegment> line_segs;
        static bool line_cmp(LineSegment line1, LineSegment line2);
    public:
        InputSet();
        // InputSet(vector<LineSegment> lines_):line_segs(lines_){}
        InputSet(vector<LineSegment> lines);        
        vector<LineSegment> get_lines();
        void put_lines(vector<LineSegment> lines);
        void append_line(LineSegment line);
        void sort_lines();
};

class ResultSet{
    // Incomplete
    private:
        InputSet* input_set_ref;
    public:
        ResultSet();
        ResultSet(InputSet* inp_set);
};

#endif