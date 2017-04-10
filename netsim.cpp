#include "netsim.h"

void NetSim::input(){
    if (::keys[GLFW_KEY_ESCAPE])
        m_running = false;
    if (::rebuild){
    	rebuildSensors();
    	rebuild = false;
    }
    if(::keys[GLFW_KEY_SPACE])
    	m_nextPeriod = true;
    if(::keys[GLFW_KEY_X])
		m_mode = Modes::GRAPH;
           
	if(::keys[GLFW_KEY_Z]) 
		m_mode = Modes::SIM;
    if(::nextPeriod){
    	m_nextPeriod = true;
    	nextPeriod = false;
    }
    if(::nextSensors){
    	if(m_curSensors < 3)
    		m_curSensors++;
    	else
    		m_curSensors  = 0;
    	::nextSensors = false;
    	redraw();
    }

}

NetSim::NetSim(GLFWwindow* window,const int numSensors):
m_textShader("textShader.vs", "textShader.frag"),
m_sensShader("shader.vs","shader.frag"),
m_graphShader("graph.vs","graph.frag"),
m_textEngine(&m_textShader),
m_numSensors(numSensors),
m_curSensors(0),
m_mode(Modes::SIM)
{
	m_window = window;
	m_running = false;

}

void NetSim::redraw(){
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_sensShader.Use();

	if(m_mode == Modes::SIM){
		m_sensors[m_curSensors].draw();
		//m_sensors.drawInts();		
	}

	if(m_mode == Modes::GRAPH)
		m_sensors[m_curSensors].drawGraph();

	std::stringstream alive;
	alive << std::fixed << std::setprecision(1) << (double)m_sensors[m_curSensors].getAlive()/m_numSensors *100;
	std::stringstream active;
	active << std::fixed << std::setprecision(1) << (double)m_sensors[m_curSensors].getActive()/m_numSensors *100;
		std::stringstream coverage;
	coverage << std::fixed << std::setprecision(1) << (double)m_sensors[m_curSensors].getCoverage() *100;
	m_textEngine.render("Algorithm: " + std::to_string(1+m_sensors[m_curSensors].m_algorithm) +
		" Alive: " + alive.str() + 
		"% Active: " + active.str() +  
		"% Intersections: " + std::to_string(m_sensors[m_curSensors].getInts()) + 
		" Coverage: " + coverage.str() + 
		"% Period: " + std::to_string(m_sensors[m_curSensors].getOptTimes()) 
		, 0.0, 0.0f, 0.5f, glm::vec3(1.0f,1.0f,1.0f));

	glfwSwapBuffers(m_window);
}

void NetSim::rebuildSensors(){
	m_sensors.clear();
	std::vector<Sensor*> tS[4];

	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_real_distribution<GLfloat> rPos(-1.0,1.0);
	std::uniform_real_distribution<GLfloat> rRad((float)10/WINDOW::MAP_SIZE_H,(float)10/WINDOW::MAP_SIZE_W);
	std::uniform_real_distribution<GLfloat> rColor(0.0,1.0);

	for(int i = 0; i < m_numSensors;i++){

		glm::vec2 position = glm::vec2(rPos(gen),rPos(gen));
		GLfloat radius = rRad(gen);

		for(int j= 0 ; j < 4 ;j++){
			Sensor* temp = new Sensor(position,rRad(gen),glm::vec3(rColor(gen),rColor(gen),rColor(gen))); 
			temp->active = true;
			tS[j].push_back(temp);
		}


	}

	
	for(int i = 0; i < 4;i++)
		m_sensors[i].build(tS[i],i);
	
}

void NetSim::run(){
	for(int i = 0; i < 4; i++)
		m_sensors.push_back(Sensors (m_sensShader,m_graphShader,m_numSensors,5));



	m_running = true;
	m_rebuild = false;
	m_nextPeriod = false;


	rebuildSensors();

	// Function alive(0,glm::vec3(1.0f,0.0f,0.0f));
	// Function grid(1,glm::vec3(1.0f,1.0f,1.0f));
	// Function active(2,glm::vec3(0.0f,0.0f,1.0f));

	// Line v(glm::vec2(0.0f,1.0f),glm::vec2(0.0f,-1.0f));
	// Line h(glm::vec2(-1.0f,0.0f),glm::vec2(1.0f,0.0f));

	// m_graph.addFunction(alive);
	// m_graph.addFunction(grid);
	// m_graph.addFunction(active);

	// m_graph.addLine(h,1);
	// m_graph.addLine(v,1);



	int testC = 0;

	while(m_running){
		glfwPollEvents();

		if(m_nextPeriod){
			m_nextPeriod = false;

			//std::cout << (float)(m_sensors.getAlive())/m_numSensors << std::endl;

			for(int i = 0; i < 4;i++)
				m_sensors[i].optimize();
			//std::cout << (double)m_sensors.getAlive()/m_numSensors << std::endl << std::endl;


		}
		redraw();
		input();
	}
}


