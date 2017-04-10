#include "graph.h"

Graph::Graph(Shader& shader):
m_shader(&shader),
m_verts(0)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, & m_vbo);
}

void Graph::buffer(){
	m_buffer.clear();
	m_verts = 0;
	for(GLuint i = 0; i < m_functions.size();i++){
		for(GLuint j= 0; j < m_functions[i].m_lines.size();j++){
			m_buffer.push_back(m_functions[i].m_lines[j].m_p1.x);
			m_buffer.push_back(m_functions[i].m_lines[j].m_p1.y);

			m_verts++;

			m_buffer.push_back(m_functions[i].m_color.x);
			m_buffer.push_back(m_functions[i].m_color.y);
			m_buffer.push_back(m_functions[i].m_color.z);
			m_verts++;

			m_buffer.push_back(m_functions[i].m_lines[j].m_p2.x);
			m_buffer.push_back(m_functions[i].m_lines[j].m_p2.y);
			m_verts++;
			
			m_buffer.push_back(m_functions[i].m_color.x);
			m_buffer.push_back(m_functions[i].m_color.y);
			m_buffer.push_back(m_functions[i].m_color.z);
			m_verts++;

		}

	}

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,m_buffer.size() * sizeof(GLfloat), &m_buffer[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0);
}

void Graph::draw(){
	m_shader->use();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_LINES, 0, m_verts);
	glBindVertexArray(0);

}