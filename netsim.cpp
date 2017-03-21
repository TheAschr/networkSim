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
m_graphShader("graph.vs","graph.frag"),
m_textEngine(&m_textShader),
m_sensors(m_sensShader,numSensors,5),
m_numSensors(numSensors),
m_graph(m_graphShader)
{
	m_window = window;
	m_running = false;

}

void NetSim::redraw(){
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_sensShader.Use();

	//m_sensors.draw();
	//m_sensors.drawInts();
	
	m_graph.draw();

	std::stringstream alive;
	alive << std::fixed << std::setprecision(1) << (double)m_sensors.getAlive()/m_numSensors *100;
	std::stringstream active;
	active << std::fixed << std::setprecision(1) << (double)m_sensors.getActive()/m_numSensors *100;
	m_textEngine.render("Alive: " + alive.str() + 
		"% Active: " + active.str() +  
		"% Intersections: " + std::to_string(m_sensors.getInts()) + 
		" Period: " + std::to_string(m_sensors.getOptTimes()) 
		, 0.0, 0.0f, 0.5f, glm::vec3(1.0f,1.0f,1.0f));

	glfwSwapBuffers(m_window);
}

void NetSim::run(){


	m_running = true;
	m_rebuild = false;
	m_nextPeriod = false;

	m_sensors.build(m_numSensors);


	Function alive(0,glm::vec3(1.0f,1.0f,1.0f));
	Function grid(1,glm::vec3(1.0f,1.0f,1.0f));
	Function active(2,glm::vec3(1.0f,1.0f,1.0f));

	Line v(glm::vec2(0.0f,1.0f),glm::vec2(0.0f,-1.0f));
	Line h(glm::vec2(-1.0f,0.0f),glm::vec2(1.0f,0.0f));

	m_graph.addFunction(alive);
	m_graph.addFunction(grid);
	m_graph.addFunction(active);

	m_graph.addLine(h,1);
	m_graph.addLine(v,1);


	m_graph.buffer();

	int testC = 0;

	while(m_running){
		glfwPollEvents();

		if(m_rebuild){
			m_rebuild = false;
			m_sensors.build(m_numSensors);
			//m_graph.resetFunction(0);
			//m_graph.resetFunction(2);
		}

		if(m_nextPeriod){
			m_nextPeriod = false;

			glm::vec2 lastAlive((float)m_sensors.getOptTimes()*0.1f,(float)(m_sensors.getAlive())/(float)m_numSensors);
			glm::vec2 lastActive((float)m_sensors.getOptTimes()*0.1f,(float)(m_sensors.getActive())/(float)m_numSensors);
			std::cout << (float)(m_sensors.getAlive())/m_numSensors << std::endl;

			m_sensors.optimize();
			//std::cout << (double)m_sensors.getAlive()/m_numSensors << std::endl << std::endl;

			glm::vec2 currAlive((float)m_sensors.getOptTimes()*0.1f,(float)(m_sensors.getAlive())/(float)m_numSensors);
			glm::vec2 currActive((float)m_sensors.getOptTimes()*0.1f,(float)(m_sensors.getActive())/(float)m_numSensors);

			Line aliveL(currAlive,lastAlive);
			Line activeL(currActive,lastActive);
			//std::cout << "(" << lastAlive.x  << "," << lastAlive.y << ")" << " to " << "(" << currAlive.x << "," << currAlive.y << ")" << std::endl;
			m_graph.addLine(aliveL,0);
			m_graph.addLine(activeL,2);
			m_graph.buffer();
		}
		redraw();
		input();
	}
}


