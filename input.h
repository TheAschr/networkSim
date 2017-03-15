#ifndef input_h
#define input_h

#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


extern bool keys[1024];
extern bool rebuild;
extern bool nextPeriod;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

#endif /* input_h */
