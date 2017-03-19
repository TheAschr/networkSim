#include "sensors.h"

Sensors::Sensors(Shader& shader,const int numSensors,const int sensRad):
m_intersections(0),
m_shader(&shader),
m_numSens(numSensors),
m_sensRad(sensRad),
m_active(numSensors),
m_alive(numSensors),
m_optTimes(0)
{


}

void Sensors::build(const int numSensors){

	m_sensors.clear();
	m_intersections = 0;

	glm::vec2 position;

	std::random_device rd;  
	std::mt19937 gen(rd());
	std::uniform_real_distribution<GLfloat> rPos(-1.0,1.0);
	std::uniform_real_distribution<GLfloat> rRad(0.05,0.5);
	std::uniform_real_distribution<GLfloat> rColor(0.0,1.0);

	for(int i = 0; i < numSensors;i++){

		position = glm::vec2(rPos(gen),rPos(gen));
		//Sensor* temp = new Sensor(position,(5.0f/WINDOW::MAP_SIZE_W),glm::vec3(rColor(gen),rColor(gen),rColor(gen)));
		Sensor* temp = new Sensor(position,rRad(gen),glm::vec3(rColor(gen),rColor(gen),rColor(gen))); 
//		Sensor* temp = new Sensor(*m_shader,position,0.2f,SENSOR::COLORS[0]); 

		temp->active = true;
		m_sensors.push_back(temp);
	}
	 setInts();
}

// Sensors::Sensors(Sensors& sensors){
// 	m_intersections = sensors.getInts();
// 	m_sensors = sensors.getSensors();
// }


void Sensors::draw(){
	//sin(glfwGetTime())/2+0.5
	for(int i = 0; i < m_sensors.size();i++){
		if(m_sensors[i]->active)
			m_sensors[i]->draw(*m_shader);
	}
}

void Sensors::setInts(){
	m_intersections = 0;
	for(int i = 0; i < m_sensors.size();i++){
		if(m_sensors[i]->active){
			for(int j = 0; j < m_sensors.size();j++){
				m_sensors[i]->setInts(*m_sensors[j]);
			}
		}

		m_intersections+=m_sensors[i]->m_intersections.size();

	}
}

void Sensors::drawInts(){
	for(int i = 0; i < m_sensors.size();i++){
		if(m_sensors[i]->active && m_sensors[i]->m_energy>0)
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


void Sensors::setActive(){

	for(int i = 0; i < m_sensors.size();i++){
		if(m_sensors[i]->active)
			m_sensors[i]->m_energy-=100;
		if(m_sensors[i]->m_energy <=0){
			m_sensors[i]->alive = false;
			m_alive--;
			m_sensors[i]->active = false;
		}
		if(m_sensors[i]->alive){
			if(m_sensors[i]->m_intersections.size()){
//			float time1 = glfwGetTime();

			if(redundant(m_sensors[i]))
				m_sensors[i]->active = false;	
			else
				m_sensors[i]->active = true;						
			// std::cout << "Redundancy Time: " << time1 - glfwGetTime() << std::endl;

			}

		}

	}



}

void Sensors::optimize() {
	//Sensors* optSensor = new Sensors(*this);
	//Sensors* optSensor(*m_shader,m_numSens,m_sensRad);
	//Sensors optSensor(*m_shader,m_numSens,m_sensRad);
	float time1 = glfwGetTime();
	//std::cout << m_alive << std::endl;
	//std::cout << "TEST" << std::endl;
	m_optTimes++;
	setActive();
	//optSensor->build(optSensor->getActive());

	//optSensor->setActive();
	//optSensor->setInts();
	std::cout << "Time to setActive: " << glfwGetTime() - time1 << std::endl;
	//time1 = glfwGetTime();
	//optSensor->setInts();
	//std::cout << "Time to set INTERSECTIONS: " << glfwGetTime() - time1 << std::endl;
	//std::cout << optSensor << std::endl;
//	return &*this;
}