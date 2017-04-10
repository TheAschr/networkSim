#include "window.h"

GLFWwindow* WINDOW::initWindow(std::string name){

    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(SCREEN_W, SCREEN_H, name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    
    glewInit();
    
    int scr_w,scr_h;
    glfwGetFramebufferSize(window, &scr_w,&scr_h);
    
    glViewport(0,0,scr_w,scr_h);
    
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window, key_callback);
    
    if ( !window )
    {
        glfwTerminate( );
        std::cout << "Error building window" << std::endl;
        return NULL;
    }
    else
        return window;
}

