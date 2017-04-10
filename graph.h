#ifndef graph_h
#define graph_h

#include <vector>

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "shader.h"

#include "glm/glm.hpp"

struct Line
{
	Line(glm::vec2 p1, glm::vec2 p2) : m_p1(p1), m_p2(p2){}
	glm::vec2 m_p1;
	glm::vec2 m_p2;
};

struct Function
{
	Function(GLuint id,glm::vec3 color){
		m_id = id;
		m_color = color;
	}
	std::vector<Line> m_lines;
	glm::vec3 m_color;
	GLuint m_id;

};

class Graph{
	public:
		Graph(Shader& shader);
		~Graph(){

		}

		void addFunction(Function& function){
			m_functions.push_back(function);
		}

		void resetFunction(GLuint id){
			for(int i = 0; i < m_functions.size();i++)
				if(m_functions[i].m_id == id)
					m_functions[i].m_lines.clear();
			buffer();
		}

		void addLine(Line& line,GLuint id){
			for(int i = 0; i < m_functions.size();i++)
				if(m_functions[i].m_id == id)
					m_functions[i].m_lines.push_back(line);
		}

		void draw();
		void buffer();
		void clear(){
			m_functions.clear();
			m_buffer.clear();
		}

	private:
		std::vector<Function> m_functions;
		std::vector<GLfloat> m_buffer;
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_verts;

		Shader* m_shader;
};

#endif