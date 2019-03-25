cmake_minimum_required( VERSION 3.0 )

project( intersecting-lines )

find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)

# flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# include
include_directories( ./include ./src)

# target
add_executable(line-intersection
                ./src/main.cpp
                ./src/primitives.cpp
                ./src/containers.cpp
                ./src/graphix.cpp
                ./src/Status.cpp
                ./src/LineSegmentIntersector.cpp
            )

target_link_libraries(line-intersection glfw ${OPENGL_LIBRARY})
