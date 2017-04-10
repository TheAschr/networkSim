#ifndef window_h
#define window_h

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <string>

#include "input.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

namespace WINDOW{
	const GLfloat SCREEN_W = 3840;
	const GLfloat SCREEN_H = 2160;

	const GLuint MAP_SIZE_W = 50;
	const GLuint MAP_SIZE_H = 50;
	const GLuint MAP_SIZE = MAP_SIZE_W * MAP_SIZE_H;

	GLFWwindow* initWindow(std::string name);

}

#endif /* window_h */
