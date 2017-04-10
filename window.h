//  window.h

#ifndef window_h
#define window_h

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <string>

#include "input.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

namespace WINDOW{
	const GLfloat SCREEN_W = 1080;
	const GLfloat SCREEN_H = 1080;

	const GLint MAP_SIZE_W = 50;
	const GLint MAP_SIZE_H = 50;
	const GLint MAP_SIZE = MAP_SIZE_W * MAP_SIZE_H;

	GLFWwindow* initWindow(std::string name);

}



#endif /* window_h */
