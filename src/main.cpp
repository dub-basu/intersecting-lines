#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "LineSegmentIntersector.h"
// #include "LSIGraphix.h"
using namespace std;

#define DEFAULT_FILENAME "../src/test.txt"

// void init_graphix_class(LSIGraphix* x){
//     x->loopie();
// }


void get_lines_from_file(string filename, vector<LineSegment>& all_lines){
    all_lines.clear();
    ifstream fin;
    fin.open(filename, ios::in);
    string p1,p2;
    string comma = ",";
    while(fin >> p1 >> p2){

        p1 = p1.substr(1, p1.size() - 2);
        p2 = p2.substr(1, p2.size() - 2);

        string p1_x = p1.substr(0,p1.find(comma));
        string p1_y = p1.substr(p1.find(comma) + 1, p1.size());

        string p2_x = p2.substr(0,p2.find(comma));
        string p2_y = p2.substr(p2.find(comma) + 1, p2.size());

        Point point_1(stold(p1_x), stold(p1_y));
        Point point_2(stold(p2_x), stold(p2_y));
        LineSegment new_line(point_1, point_2);

        all_lines.push_back(new_line);
    }
    fin.close();
}

int main(int argc, char** argv){

    // std::mutex mtx;
    // LSIGraphix gfx(mtx);
    // thread t1(init_graphix_class, &gfx);

    string filename;
    if(argc > 1){
        filename = argv[1];
        cout << filename << endl;
    } else {
        filename = DEFAULT_FILENAME;
    }

    vector<LineSegment> all_lines;
    get_lines_from_file(filename, all_lines);

    LineSegmentIntersector lsi(all_lines);
    LSIResult res = lsi.computeIntersections();
    cout << "RESULT:\n";

    for (auto i : res){
        cout << i.first << " : ";
        cout << i.second.size() << "\n";
        for (auto j : i.second){
            cout << "\t" << j << "\n";
        }
    }

    // t1.join();
    return 0;
}
