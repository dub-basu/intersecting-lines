cmake_minimum_required( VERSION 3.0 )

project( intersecting-lines )

find_package(OpenGL REQUIRED)
find_package(GLUT)
find_package(glfw3 3.2 REQUIRED)

# flags
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# add_subdirectory(./external/glfw)

# include
include_directories( ./include ./src)

# target
add_executable(line-intersection
                ./src/main.cpp
                ./src/primitives.cpp
                ./src/components.cpp
                ./src/containers.cpp
                ./src/graphix.cpp
            )

target_link_libraries(line-intersection glfw)
target_link_libraries(line-intersection ${OPENGL_LIBRARY})

# target_include_directories(line-intersection ${OPENGL_INCLUDE_DIR})
# target_link_libraries(line-intersection ${OPENGL_glu_LIBRARY})

# remove for glut
target_link_libraries(line-intersection ${OPENGL_LIBRARY} ${GLUT_LIBRARY})

