#include "input.h"

bool keys[1024];

bool rebuild = false;

bool nextPeriod = false;

bool back = false;

bool nextSensors = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
    
    if((key == GLFW_KEY_R) && (action == GLFW_RELEASE)){
        rebuild = true;
    }
    else
        rebuild = false;
    
    if((key == GLFW_KEY_SPACE) && (action == GLFW_RELEASE)){
        nextPeriod = true;
    }
    else
        nextPeriod = false;

    if((key == GLFW_KEY_Z) && (action == GLFW_RELEASE)){
        back = true;
    }
    else
        back = false;  


    if((key == GLFW_KEY_ENTER) && (action == GLFW_RELEASE)){
        nextSensors = true;
    }
    else
        nextSensors = false;     
}
