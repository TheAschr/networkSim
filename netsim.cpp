#include "netsim.h"

void NetSim::input(){
    if (::keys[GLFW_KEY_ESCAPE])
        m_running = false;
    if (::rebuild){
    	m_rebuild = true;
    	rebuild = false;
    }
    if(::keys[GLFW_KEY_SPACE])
    	m_nextPeriod = true;
   /*
    if(::nextPeriod){
    	m_nextPeriod = true;
    	nextPeriod = false;
    }
    */

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

	if(!m_states.empty()){
		m_states.top()->draw();
		m_states.top()->drawInts();
	}



	m_textEngine.render("Intersections: " + std::to_string(m_sensors.getInts()) + " Period: " + std::to_string(m_states.top()->getOptTimes()) , 0.0, 0.0f, 0.5f, glm::vec3(1.0f,0.0f,0.0f));

	glfwSwapBuffers(m_window);
}

void NetSim::run(){


	m_running = true;
	m_rebuild = false;
	m_nextPeriod = false;
	m_period = 0;

	m_sensors.build(m_numSensors);
	m_states.push(&m_sensors);
	redraw();

	GLfloat time1,time2;

	while(m_running){
		glfwPollEvents();

		if(m_rebuild){
			m_rebuild = false;
			while(!m_states.empty())
				m_states.pop();
			m_sensors.build(m_numSensors);
			m_states.push(&m_sensors);			
		}

		if(m_nextPeriod){
			m_nextPeriod = false;
			//m_states.pop();
			//time1 = glfwGetTime();
			m_states.push(m_states.top()->optimize());
			//time2 = glfwGetTime();
			//std::cout << "Time to optimize: " << time2 - time1 << std::endl;
		}
		time1 = glfwGetTime();
		redraw();
		//std::cout << "Time to redraw: " << time2 - time1 << std::endl;
		time2 = glfwGetTime();
		input();
	}
}


