//
//  main.cpp
//
//  Created by Alex Schrimpf on 2/12/17.
//  Copyright © 2017 Alex Schrimpf. All rights reserved.
//

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "window.h"
#include "netsim.h"

int NUM_SENSORS = 200;

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    GLFWwindow* window = WINDOW::initWindow("Network Simulator");
    NetSim network(window,NUM_SENSORS);
    network.run();
    glfwTerminate();
    return 0;
}
