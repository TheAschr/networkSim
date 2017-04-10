#ifndef netsim_h
#define netsim_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "input.h"
#include "window.h"
#include "circle.h"
#include <vector>
#include <stack>
#include "shader.h"
#include "sensors.h"
#include <sstream>
#include "graph.h"

#include "glm/ext.hpp"
#include "text.h"

#include "graph.h"

enum class MODES { SIM , GRAPH };

class NetSim{
	public:
		NetSim(GLFWwindow* window,const GLuint numSensors);

		void run();

	private:
		
		GLFWwindow* m_window;

		bool m_running;

		void input();
		void redraw();
		void rebuildSensors();
	
		std::vector<Sensors> m_sensors;
	
		SENSOR::ALGORITHMS m_curSensors;

		Text m_textEngine;

		Shader m_sensShader;
		Shader m_textShader;
		Shader m_graphShader;

		GLuint m_numSensors;
		MODES m_mode;

};

#endif