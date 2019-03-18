#include<vector>
#include "containers.h"

InputSet::InputSet(){}

InputSet::InputSet(vector<LineSegment> lines){
    put_lines(lines);
}

vector<LineSegment> InputSet::get_lines(){
    return(line_segs);
}

void InputSet::put_lines(vector<LineSegment> lines){
    line_segs = lines;
}

void InputSet::append_line(LineSegment line){
    line_segs.push_back(line);
}

void InputSet::sort_lines(){
    // Not required right now. Add as required.
}

ResultSet::ResultSet(){}

ResultSet::ResultSet(InputSet* inp_set){
    input_set_ref = inp_set;
}