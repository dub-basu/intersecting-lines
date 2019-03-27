#ifndef WINDOWCONSTANTS
#define WINDOWCONSTANTS

#define BG_COLOR 1.0, 1.0, 1.0
#define BG_ALPHA 1.0
#define DRAW_COLOR 1.0, 0.0, 0.0

#define WIN_BREADTH 540
#define WIN_HEIGHT 540
#define WIN_POSITION_X 0
#define WIN_POSITION_Y  0
#define WIN_DIM_NEG_X -20
#define WIN_DIM_POS_X 20
#define WIN_DIM_NEG_Y -20
#define WIN_DIM_POS_Y 20

#define WIN_NAME "Graphix"
#define POINT_SIZE 8.0

#endif

#ifndef GRAPHIX
#define GRAPHIX

#include "primitives.h"
#include<vector>
#include<GLFW/glfw3.h> 
#include<mutex>

class Graphix{
    public:
        std::mutex& m_mutex; 
        static bool render_wait_flag;
        GLFWwindow* window;
        Graphix(std::mutex& mtx);
        void draw_line(LineSegment line);
        void draw_dashed_line(LineSegment line);
        void loopie();
        void render();
        void clear();
    private:
        static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
        static void cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos);
        static void error_callback(int error, const char* description);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void window_refresh_callback(GLFWwindow* window);
        static void cursor_enter_callback(GLFWwindow* window, int entered);
};

#endif