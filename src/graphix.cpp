#include<GLFW/glfw3.h> 
#include<iostream>
#include "graphix.h"
// #include<mutex>

using namespace std;

void Graphix::cursor_position_callback(GLFWwindow* window, double x_pos, double y_pos){
    // cout << "x: " << x_pos << "\t" << "y: " << y_pos << endl;
    // glfwWaitEvents();
}

void Graphix::mouse_button_callback(GLFWwindow* window, int button, int action, int mode){
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        cout << "left button pressed" << endl;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        cout << "left button released" << endl;
    }
}

void Graphix::error_callback(int error, const char* description){
    fputs(description, stderr);
}

void Graphix::window_refresh_callback(GLFWwindow* window){
    // glfwWaitEvents();
    // cout << "window refresh" << endl;

}

void Graphix::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if(key == GLFW_KEY_Q && action == GLFW_PRESS){
        cout << "entered Q" << endl;
    }
    else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        render_wait_flag = true;
        glfwPostEmptyEvent();
    }
    else{
        // glfwWaitEvents();
    }
}

void Graphix::cursor_enter_callback(GLFWwindow* window, int entered){
    // glfwWaitEvents();
}

void Graphix::draw_dashed_line(LineSegment line){

    glPushAttrib(GL_ENABLE_BIT); 
    glLineStipple(1, 0x1111);
    glEnable(GL_LINE_STIPPLE);
    draw_line(line);
    glPopAttrib();

}

void Graphix::render(){
    // while(render_wait_flag == false) glfwWaitEvents();
    m_mutex.lock();
    // render_wait_flag = true;
    while(render_wait_flag == false) glfwWaitEvents();
    glfwSwapBuffers(window);
    render_wait_flag = false;
    m_mutex.unlock();
}

void Graphix::draw_line(LineSegment line){
    glBegin(GL_LINES);
        glVertex2f(line.start_pt().x, line.start_pt().y);
        glVertex2f(line.end_pt().x, line.end_pt().y);
    glEnd();
}

// void init(){

// }

void Graphix::loopie(){
    while( !glfwWindowShouldClose(window) ){
        glfwWaitEvents();
        // cout << "ggwp" << endl;
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Graphix::render_wait_flag = false; 

Graphix::Graphix(std::mutex& mtx):m_mutex(mtx){
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    window = glfwCreateWindow(WIN_HEIGHT, WIN_HEIGHT, WIN_NAME, NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    render_wait_flag = false;

    // Set common callbacks
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;

    glClearColor(BG_COLOR, BG_ALPHA);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(WIN_DIM_NEG_X, WIN_DIM_POS_X, WIN_DIM_NEG_Y, WIN_DIM_POS_Y, 1.f,-1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}