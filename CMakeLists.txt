cmake_minimum_required( VERSION 3.0 )

project( intersecting-lines )

# flags

# include
include_directories( ./include ./src)

# target
add_executable(line-intersection ./src/main.cpp ./src/primitives.cpp ./src/components.cpp )