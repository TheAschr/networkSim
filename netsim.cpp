#include "netsim.h"

void NetSim::input(){
    if (::keys[GLFW_KEY_ESCAPE])
        m_running = false;
    if (::rebuild){
    	m_rebuild = true;
    	rebuild = false;
    }
   // if(::keys[GLFW_KEY_SPACE])
    //	m_nextPeriod = true;
    if(::keys[GLFW_KEY_Z]){
    	//std::cout << m_states.back() << std::endl;
		//if(m_states.size()>1)
    	//	m_states.pop_back();
    		//m_states.push_back(m_states[1]);
		back = false;
    }


   
    if(::nextPeriod){
    	m_nextPeriod = true;
    	nextPeriod = false;
    }
    

}

NetSim::NetSim(GLFWwindow* window,const int numSensors):
m_textShader("textShader.vs", "textShader.frag"),
m_sensShader("shader.vs","shader.frag"),
m_textEngine(&m_textShader),
m_sensors(m_sensShader,numSensors,5),
m_numSensors(numSensors)
{
	m_window = window;
	m_running = false;

}

void NetSim::redraw(){
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_sensShader.Use();

	m_sensors.draw();

	m_textEngine.render("Alive: " + std::to_string(m_sensors.getAlive()) + " Active: " + std::to_string(m_sensors.getActive()) +  " Intersections: " + std::to_string(m_sensors.getInts()) + " Period: " + std::to_string(m_sensors.getOptTimes()) , 0.0, 0.0f, 0.5f, glm::vec3(1.0f,1.0f,1.0f));

	glfwSwapBuffers(m_window);
}

void NetSim::run(){


	m_running = true;
	m_rebuild = false;
	m_nextPeriod = false;

	m_sensors.build(m_numSensors);

	GLfloat time1,time2;

	while(m_running){
		glfwPollEvents();

		if(m_rebuild){
			m_rebuild = false;
			m_sensors.build(m_numSensors);
		}

		if(m_nextPeriod){
			m_nextPeriod = false;
			m_sensors.optimize();
		}
		time1 = glfwGetTime();
		redraw();
		//std::cout << "Time to redraw: " << time2 - time1 << std::endl;
		time2 = glfwGetTime();
		input();
	}
}


