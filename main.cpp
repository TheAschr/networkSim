#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "netsim.h"

int main(int argc, const char * argv[]) {
	
	if(argv[1]){
		srand(time(NULL));
   		
   		GLFWwindow* window = WINDOW::initWindow("Network Simulator");
    	NetSim network(window,atoi(argv[1]));
    	
    	network.run();
    	
    	glfwTerminate();
	}
	else
		printf("Enter a number as an argument\n");
    
    return 0;
}
