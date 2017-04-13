#ifndef sensors_h
#define sensors_h

#include "circle.h"
#include "glm/glm.hpp"

#include <vector>
#include <random>
#include "window.h"
#include <iomanip>
#include "graph.h"
#include <algorithm>
#include "colors.h"

namespace SENSOR{
	const GLuint DEFAULT_ENERGY = 300;
	const GLuint DEFAULT_ENERGY_LOSS = 1;
	const GLuint DEFAULT_PRECISION = 9;
	const GLfloat DEFAULT_RADIUS_LOWER = 10.0f;
	const GLfloat DEFAULT_RADIUS_UPPER = 10.0f;
	const GLfloat DEFAULT_COLOR_LOWER = 0.0f;
	const GLfloat DEFAULT_COLOR_UPPER = 1.0f;

	//lower is faster
	const GLfloat DEFAULT_GRAPH_SPEED = 0.005f;
	const glm::vec2 NORMALIZED_VECS(-1.0f,1.0f);
	const glm::vec3  COLORS[3] = {glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f) };
	enum class ALGORITHMS { RAND_BOT_UP, RAND_TOP_DOWN, ALL_ACTIVE, WEIGHTED_BOT_UP, SIZE = int(WEIGHTED_BOT_UP) };
}
namespace INTERSECTIONS{
	const GLuint DEFAULT_PRECISION = 7;
	const GLfloat DEFAULT_RAD = 0.005f;
}
struct Sensor
{

	Sensor(glm::vec2& position,GLfloat radius,glm::vec3 color):
		m_energy(SENSOR::DEFAULT_ENERGY),
		m_position(position),
		m_radius(radius),
		m_color(color),
		m_circle(position,radius,SENSOR::DEFAULT_PRECISION),
		active(true){}

	void draw(Shader& shader){
		if(active)
			m_circle.draw(shader,glm::vec4(SENSOR::COLORS[1],(float)m_energy/SENSOR::DEFAULT_ENERGY));
		else
			m_circle.draw(shader,glm::vec4(SENSOR::COLORS[0],(float)m_energy/SENSOR::DEFAULT_ENERGY));
	}

	void setIntersects(Sensor& sensor){
		std::vector<glm::vec2> temp(m_circle.getIntersects(sensor.m_circle));
		m_intersections.insert(m_intersections.end(),temp.begin(),temp.end());
	}

	bool active;
	GLfloat m_radius;
	GLuint m_energy;
	glm::vec3 m_color;
	glm::vec2 m_position;

	Circle m_circle;

	std::vector<glm::vec2> m_intersections;
};

class Sensors{
	public:
		Sensors(Shader& shader,Shader& gShader,const GLuint numSensors,const GLuint sensRad);
		virtual ~Sensors(){
			m_sensors.clear();
		}
		void draw();
		void drawIntersects();
		void drawGraph(){m_graph.draw(m_optTimes*(float)SENSOR::DEFAULT_ENERGY_LOSS*SENSOR::DEFAULT_GRAPH_SPEED);}

		void build(std::vector<Sensor*> sensors,const SENSOR::ALGORITHMS algorithm);
		
		GLuint getIntersects() const {return m_intersections;}	
		GLuint getAlive() const {return m_sensors.size();}
		GLuint getActive() const {return m_active;}
		GLuint getOptTimes() const {return m_optTimes;}

		GLfloat getEnergy(){
			GLfloat e = 0;

			for(int i =0; i < m_sensors.size();i++)
				e+=m_sensors[i]->m_energy;

			return (e/m_sensors.size());
		}

		void optimize();
		float getCoverage(){return m_coverage;}
		void setCoverage(const GLuint precision);

		SENSOR::ALGORITHMS m_algorithm;
	private:

		bool redundant(Sensor* sensor);
	
		void randTopDown();
		void randBotUp();
		void allActive();
		void weightedBotUp();
	
		bool setPower();
		void setIntersects();
		void setActive();

		GLuint nonCoveredPoints(Sensor *s0);

		Shader* m_shader;
		GLuint m_sensRad;
		std::vector<Sensor*> m_sensors;
		
		GLuint m_intersections;
		GLuint m_active;
		GLuint m_numSens;
		GLuint m_optTimes;
		float m_energy;

		float m_coverage;

		Graph m_graph;
		Shader* m_graphShader;
		Function alive;
		Function grid;
		Function active;
		Function coverage;
		Function energy;

		Line v;
		Line h;

};

#endif
