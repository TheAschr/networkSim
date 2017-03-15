//
//  window.cpp
//  Yarudake
//
//  Created by Alex Schrimpf on 2/12/17.
//  Copyright © 2017 Alex Schrimpf. All rights reserved.
//

#include "window.h"

GLFWwindow* WINDOW::initWindow(std::string name){
    
    //Initaliaze GLFW
    glfwInit();
    
    //Use glfw version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Need for osx
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //create GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(SCREEN_W, SCREEN_H, name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    //Disable the cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glewExperimental = GL_TRUE;
    
    //Initalize GLEW
    glewInit();
    
    //build a viewport
    int scr_w,scr_h;
    glfwGetFramebufferSize(window, &scr_w,&scr_h);
    
    glViewport(0,0,scr_w,scr_h);
    
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //setup input
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

