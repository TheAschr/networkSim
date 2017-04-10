#include "sensors.h"

Sensors::Sensors(Shader& shader,Shader& gShader,const int numSensors,const int sensRad):
m_intersections(0),
m_shader(&shader),
m_graphShader(&gShader),
m_graph(gShader),
m_numSens(numSensors),
m_sensRad(sensRad),
m_active(numSensors),
m_optTimes(0),
alive(0,glm::vec3(1.0f,0.0f,0.0f)),
grid(1,glm::vec3(1.0f,1.0f,1.0f)),
active(2,glm::vec3(0.0f,0.0f,1.0f)),
coverage(3,glm::vec3(0.0f,1.0f,0.0f)),
v(glm::vec2(0.0f,1.0f),glm::vec2(0.0f,-1.0f)),
h(glm::vec2(-1.0f,0.0f),glm::vec2(1.0f,0.0f))
{



}

void Sensors::build(std::vector<Sensor*> sensors,int algorithm){

	m_optTimes = 0;
	m_sensors.clear();
	m_intersections = 0;
	m_algorithm = algorithm;

	m_sensors = sensors;
	setInts();
	setActive();
	setCoverage(10000);

	for(int i =0; i < 4;i++)
		m_graph.resetFunction(i);
	
	m_graph.addFunction(alive);
	m_graph.addFunction(grid);
	m_graph.addFunction(active);
	m_graph.addFunction(coverage);

	m_graph.addLine(h,1);
	m_graph.addLine(v,1);
	m_graph.buffer();





}

void Sensors::draw(){
	for(int i = 0; i < m_sensors.size();i++)
		m_sensors[i]->draw(*m_shader);
	
}

void Sensors::setInts(){
	m_intersections = 0;
	for(int i = 0; i < m_sensors.size();i++){
		m_sensors[i]->m_intersections.clear();

		for(int j = 0; j < m_sensors.size();j++)
			m_sensors[i]->setInts(*m_sensors[j]);

		m_intersections+=m_sensors[i]->m_intersections.size();
	}
}

void Sensors::drawInts(){
	for(int i = 0; i < m_sensors.size();i++){
		for(int j =0; j < m_sensors[i]->m_intersections.size();j++){
			Circle temp(m_sensors[i]->m_intersections[j],INTERSECTIONS::DEFAULT_RAD,INTERSECTIONS::DEFAULT_PRECISION);
			temp.draw(*m_shader,glm::vec4(1.0f,1.0f,1.0f,0.3f));
		}
	}
}


bool Sensors::redundant(Sensor *s0){
	GLfloat distance;
	bool contains;
	int s1;
	for (int i = 0; i < s0->m_intersections.size();i++){
		contains = false;
		s1 = 0;
		do{
			distance = std::abs( sqrt( pow(m_sensors[s1]->m_position.x - s0->m_intersections[i].x,2) + pow(m_sensors[s1]->m_position.y - s0->m_intersections[i].y, 2) ) );
			if(m_sensors[s1]->active && distance + pow(10,-6) < m_sensors[s1]->m_radius)
				contains = true;
			else
				contains = false;
			s1++;

		}while(!contains && s1 <m_sensors.size());

		if(!contains)
			return false;	
	}
	if(s0->m_intersections.size())
		return true;
	else
		return false;

}

int Sensors::nonCoveredPoints(Sensor *s0){
	int p = s0->m_intersections.size();
	for(int i = 0; i < s0->m_intersections.size();i++){
		bool contains = false;
		int s1 = 0;
		while(s1 < m_sensors.size()){
			GLfloat distance = std::abs( sqrt( pow(m_sensors[s1]->m_position.x - s0->m_intersections[i].x,2) + pow(m_sensors[s1]->m_position.y - s0->m_intersections[i].y, 2) ) );
			if(distance + pow(10,-6) < m_sensors[s1]->m_radius)
				contains = true;
			s1++;
		}
		if(contains)
			p--;
	}
	return p;
}


void Sensors::setCoverage(const int precision){
	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_real_distribution<GLfloat> rPos(-1.0,1.0);
	
	int p = 0;

	for(int i = 0; i < precision; i++){
			glm::vec2 position = glm::vec2(rPos(gen),rPos(gen));
			bool contains = false;
			int s1 = 0;
			while(s1 < m_sensors.size() && !contains){
				GLfloat distance = std::abs( sqrt( pow(m_sensors[s1]->m_position.x - position.x,2) + pow(m_sensors[s1]->m_position.y - position.y, 2) ) );
				if(distance + pow(10,-6) < m_sensors[s1]->m_radius && m_sensors[s1]->active)
					contains = true;
				s1++;
			}
			if(contains)
				p++;
	}
	m_coverage = (float)(p)/precision;
}

void Sensors::allActive(){
	m_active = m_sensors.size();
	for(int i = 0; i < m_sensors.size();i++)
		m_sensors[i]->active = true;
}

void Sensors::randBotUp(){

	std::random_shuffle (m_sensors.begin(), m_sensors.end());

	m_active = 0;
	for(int i = 0; i < m_sensors.size();i++){
		if(!redundant(m_sensors[i])){
			m_sensors[i]->active = true;
			m_active++;
		}
		else
			m_sensors[i]->active = false;
	}
}

void Sensors::randTopDown(){
	std::random_shuffle (m_sensors.begin(), m_sensors.end());

	m_active = m_sensors.size();
	for(int i = 0; i < m_sensors.size();i++){
		if(redundant(m_sensors[i])){
			m_sensors[i]->active = false;
			m_active--;
		}
		else
			m_sensors[i]->active = true;
	}
}

void Sensors::weightedBotUp(){
	std::vector<std::pair<int, int> > temp;
	m_active = 0;
	for(int i = 0; i < m_sensors.size();i++){
		int p = nonCoveredPoints(m_sensors[i]);
		temp.push_back(std::make_pair(i,p));
	}
	std::sort(temp.begin(),temp.end(),[](auto &left, auto &right){return left.second > right.second;});

	for(int i = 0; i < temp.size();i++){
		if(!redundant(m_sensors[temp[i].first])){
			m_sensors[temp[i].first]->active = true;
			m_active++;
		}
		else
			m_sensors[temp[i].first]->active = false;
	}
}


bool Sensors::setPower(){
	std::vector<Sensor*> temp;
	bool died = false;
	for(int i = 0; i < m_sensors.size();i++){
		if(m_sensors[i]->m_energy>0)
			temp.push_back(m_sensors[i]);
		else
			died = true;
		if(m_sensors[i]->active)
			m_sensors[i]->m_energy-=SENSOR::DEFAULT_ENERGY_LOSS;
	}
	m_sensors = temp;
	return died;
}

void Sensors::setActive(){
	for(int i = 0; i< m_sensors.size();i++)
		m_sensors[i]->active =false;
		switch(m_algorithm){
			case 0:
			randBotUp();
			break;
			case 1:
			randTopDown();
			break;
			case 2:
			allActive();
			break;
			case 3:
			weightedBotUp();
			break;
		}
}

void Sensors::optimize() {
	glm::vec2 lastAlive((float)m_optTimes*0.01f,(float)(getAlive())/(float)m_numSens);
	glm::vec2 lastActive((float)m_optTimes*0.01f,(float)(getActive())/(float)m_numSens);
	glm::vec2 lastCov((float)m_optTimes*0.01f,getCoverage());

	m_optTimes++;
	if(setPower()){
		setInts();
		setActive();
		setCoverage(10000);
	}
	// setPower();
	// setInts();
	// setActive();
	// setCoverage(10000);
	
	glm::vec2 currAlive((float)m_optTimes*0.01f,(float)(getAlive())/(float)m_numSens);
	glm::vec2 currActive((float)m_optTimes*0.01f,(float)(getActive())/(float)m_numSens);
	glm::vec2 currCov((float)m_optTimes*0.01f,getCoverage());

	Line aliveL(currAlive,lastAlive);
	Line activeL(currActive,lastActive);
	Line covL(currCov,lastCov);
	//std::cout << "(" << lastAlive.x  << "," << lastAlive.y << ")" << " to " << "(" << currAlive.x << "," << currAlive.y << ")" << std::endl;
	m_graph.addLine(aliveL,0);
	m_graph.addLine(activeL,2);
	m_graph.addLine(covL,3);

	m_graph.buffer();
}