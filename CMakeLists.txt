cmake_minimum_required( VERSION 3.0 )

project( intersecting-lines )

# flags

# include
include_directories( ./include ./src)

# target
add_executable(line-intersection  ./src/Status.cpp ./src/main.cpp)##./src/primitives.cpp ./src/components.cpp src/LineSegmentIntersector.cpp src/LineSegmentIntersector.h src/Status.h)
## Removed ./src/main.cpp