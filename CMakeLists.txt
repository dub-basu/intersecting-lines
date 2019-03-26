cmake_minimum_required( VERSION 3.0 )

project( intersecting-lines )

# flags
set(CMAKE_CXX_FLAGS "-g")

# include
include_directories( ./include ./src)

# target
# target_compile_options(line-intersection -g)
add_executable(line-intersection  ./src/Status.cpp ./src/main.cpp ./src/primitives.cpp src/LineSegmentIntersector.cpp ./src/EventQueue.cpp )##./src/primitives.cpp ./src/components.cpp src/LineSegmentIntersector.cpp src/LineSegmentIntersector.h src/Status.h)
#target_compile_options(line-intersection -g)

## Removed ./src/main.cpp
