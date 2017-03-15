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

#include "glm/ext.hpp"
#include "text.h"

class NetSim{
	public:
		NetSim(GLFWwindow* window,const int numSensors);
		~NetSim(){
		};
		void run();

	private:
		GLFWwindow* m_window;

		bool m_running;
		bool m_rebuild;
		bool m_nextPeriod;
		void input();
		void redraw();
		Sensors m_sensors;
		std::stack<Sensors*> m_states;

		Text m_textEngine;

		Shader m_sensShader;
		Shader m_textShader;
		int m_numSensors;
		int m_period;
};

#endif