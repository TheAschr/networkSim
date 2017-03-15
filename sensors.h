#ifndef sensors_h
#define sensors_h

#include "circle.h"
#include "glm/glm.hpp"

#include <vector>
#include <random>
#include "window.h"
#include <iomanip>

namespace SENSOR{
	const int DEFAULT_ENERGY = 300;
	const int DEFAULT_PRECISION = 8;
	const glm::vec3  COLORS[3] = {glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f) };
}
namespace INTERSECTIONS{
	const int DEFAULT_PRECISION = 7;
	const GLfloat DEFAULT_RAD = 0.005f;
}
struct Sensor
{

	Sensor(Shader& shader,glm::vec2& position,GLfloat radius,glm::vec3 color):
		m_energy(SENSOR::DEFAULT_ENERGY),
		m_position(position),
		m_radius(radius),
		m_color(color),
		m_circle(shader,position,radius,SENSOR::DEFAULT_PRECISION),
		active(true),
		alive(true){}

	void draw(){
		//m_circle.draw(glm::vec4( glm::vec3(sin(glfwGetTime()*m_color.x)/2+0.5,sin(glfwGetTime()*m_color.y)/2+0.5,sin(glfwGetTime()*m_color.z)/2+0.5),(float)m_energy/SENSOR::DEFAULT_ENERGY));
		if(active)
			m_circle.draw(glm::vec4(SENSOR::COLORS[1],(float)m_energy/SENSOR::DEFAULT_ENERGY));
			//m_circle.draw(glm::vec4( glm::vec3(sin(glfwGetTime()*m_color.x)/2+0.5,sin(glfwGetTime()*m_color.y)/2+0.5,sin(glfwGetTime()*m_color.z)/2+0.5),(float)m_energy/SENSOR::DEFAULT_ENERGY));
		else
			m_circle.draw(glm::vec4(SENSOR::COLORS[0],(float)m_energy/SENSOR::DEFAULT_ENERGY));
			//m_circle.draw(glm::vec4(SENSOR::COLORS[0],sin(glfwGetTime()*6)/2+0.5));

	}

	void setInts(Sensor& sensor){
		std::vector<glm::vec2> temp(m_circle.getInts(sensor.m_circle));
		//for(int i = 0; i < temp.size();i++)
	//		std::cout << "Intercepts: " << temp[i].x << " " << temp[i].y << std::endl;
		m_intersections.insert(m_intersections.end(),temp.begin(),temp.end());
	}

	bool active;
	bool alive;
	GLfloat m_radius;
	int m_energy;
	glm::vec3 m_color;
	glm::vec2 m_position;

	Circle m_circle;

	std::vector<glm::vec2> m_intersections;
};

class Sensors{
	public:
		Sensors(Shader& shader,const int numSensors,const int sensRad);
		virtual ~Sensors(){
			m_sensors.clear();
		}
		void draw();
		void drawInts();

		void build(const int numSensors);
		
		int getInts(){return m_intersections;}
		int getOptTimes(){return m_optTimes;}
		void setInts();
		void setActive();
		
		Sensors* optimize();
	private:

		bool redundant(Sensor* sensor);

		Shader* m_shader;
		int m_sensRad;
		std::vector<Sensor*> m_sensors;
		int m_intersections;
		int m_active;
		int m_alive;
		int m_optTimes;

};

#endif