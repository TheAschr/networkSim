#include "netsim.h"

void NetSim::input(){
    
    if (::keys[GLFW_KEY_ESCAPE])
        m_running = false;

    if(::keys[GLFW_KEY_X])
		m_mode = MODES::GRAPH;   

	if(::keys[GLFW_KEY_Z]) 
		m_mode = MODES::SIM;

    if(::keys[GLFW_KEY_SPACE]){
		for(int i = 0; i <= (int)SENSOR::ALGORITHMS::SIZE;i++)
			m_sensors[i].optimize();    	
		nextPeriod = false;
    }

    if(::nextSensors){
    	if(m_curSensors < SENSOR::ALGORITHMS::SIZE)
    		m_curSensors = SENSOR::ALGORITHMS((int)m_curSensors + 1);
    	else
    		m_curSensors  = SENSOR::ALGORITHMS(0);
    	::nextSensors = false;
    	redraw();
    }

    if (::rebuild){
    	rebuildSensors();
    	rebuild = false;
    }

}

NetSim::NetSim(GLFWwindow* window,const GLuint numSensors):
m_textShader("textShader.vs", "textShader.frag"),
m_sensShader("shader.vs","shader.frag"),
m_graphShader("graph.vs","graph.frag"),
m_textEngine(&m_textShader),
m_numSensors(numSensors),
m_curSensors(SENSOR::ALGORITHMS::RAND_BOT_UP),
m_mode(MODES::SIM),
m_window(window),
m_running(false)
{}

void NetSim::redraw(){
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_sensShader.use();

	if(m_mode == MODES::SIM){
		m_sensors[(int)m_curSensors].draw();
		//m_sensors.drawGLuints();		
	}

	if(m_mode == MODES::GRAPH)
		m_sensors[(int)m_curSensors].drawGraph();

	std::stringstream alive;
	alive << std::fixed << std::setprecision(1) << (double)m_sensors[(int)m_curSensors].getAlive()/m_numSensors *100;
	std::stringstream active;
	active << std::fixed << std::setprecision(1) << (double)m_sensors[(int)m_curSensors].getActive()/m_numSensors *100;
		std::stringstream coverage;
	coverage << std::fixed << std::setprecision(1) << (double)m_sensors[(int)m_curSensors].getCoverage() *100;
	m_textEngine.render("Algorithm: " + std::to_string(1+(int)m_sensors[(int)m_curSensors].m_algorithm) +
		" Alive: " + alive.str() + 
		"\% Active: " + active.str() +  
		"\% GLuintersections: " + std::to_string(m_sensors[(int)m_curSensors].getIntersects()) + 
		" Coverage: " + coverage.str() + 
		"\% Period: " + std::to_string(m_sensors[(int)m_curSensors].getOptTimes()) 
		, 10.0f, 10.0f, 0.5f, glm::vec3(1.0f,1.0f,1.0f));

	glfwSwapBuffers(m_window);
}

void NetSim::rebuildSensors(){
	
	m_sensors.clear();
	std::vector<Sensor*> tS[(int)(SENSOR::ALGORITHMS::SIZE)+1];

	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_real_distribution<GLfloat> rPos(SENSOR::NORMALIZED_VECS.x,SENSOR::NORMALIZED_VECS.y);
	std::uniform_real_distribution<GLfloat> rRad(SENSOR::DEFAULT_RADIUS_LOWER/WINDOW::MAP_SIZE_H,SENSOR::DEFAULT_RADIUS_UPPER/WINDOW::MAP_SIZE_W);
	std::uniform_real_distribution<GLfloat> rColor(0.0,1.0);


	for(GLuint i = 0; i < m_numSensors;i++){
		glm::vec2 position = glm::vec2(rPos(gen),rPos(gen));
		GLfloat radius = rRad(gen);
		for(GLuint j= 0 ; j <= (int)SENSOR::ALGORITHMS::SIZE ;j++){

			Sensor* temp = new Sensor(position,rRad(gen),glm::vec3(rColor(gen),rColor(gen),rColor(gen))); 
			temp->active = true;
			tS[j].push_back(temp);
		}
	}


	for(GLuint i = 0; i <= (int)SENSOR::ALGORITHMS::SIZE;i++)
		m_sensors[i].build(tS[i],SENSOR::ALGORITHMS(i));
	
}

void NetSim::run(){
	for(int i = 0; i <= (int)SENSOR::ALGORITHMS::SIZE; i++)
		m_sensors.push_back(Sensors (m_sensShader,m_graphShader,m_numSensors,5));

	m_running = true;
	rebuildSensors();
	while(m_running){
		glfwPollEvents();
		redraw();
		input();
	}
}


