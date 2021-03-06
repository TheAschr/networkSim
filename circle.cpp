#include "circle.h"

Circle::Circle(const glm::vec2& position,const GLfloat radius,const GLuint precision) : m_position(position), m_radius(radius){

	std::vector<GLfloat> result;
	float increment = 2.0f * PI / (pow(10,precision)/(WINDOW::SCREEN_W*WINDOW::SCREEN_H));

	m_verts = 0;
	for (float currAngle = 0.0f; currAngle <= 2.0f * PI; currAngle += increment){
	    result.push_back((radius * cos(currAngle)) + m_position.x);
	    result.push_back((radius * sin(currAngle)) + m_position.y);
		m_verts++;
	}

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,result.size() * sizeof(GLfloat), &result[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0);

}


void Circle::draw(Shader& shader,const glm::vec4& color)
{
	glUniform4fv(glGetUniformLocation(shader.Program, "vColor"), 1, glm::value_ptr(color));
	glBindVertexArray(m_vao);
	glDrawArrays(GL_LINE_LOOP, 0, m_verts);
	glBindVertexArray(0);
}


std::vector<glm::vec2> Circle::getIntersects(const Circle& circle) const{
	
	std::vector<glm::vec2> temp;

	GLfloat r1 = circle.getRad();
	glm::vec2 p1(circle.getPos().x,circle.getPos().y);

	GLfloat d = std::abs( sqrt( pow(p1.x - m_position.x,2) + pow(p1.y - m_position.y, 2) ) );
	if(!(d < std::abs(m_radius-r1) || d > (m_radius+r1) || !d)){
		GLfloat a = (pow(m_radius,2) - pow(r1,2) + pow(d,2)) / (2*d);
		GLfloat h = sqrt( pow(m_radius,2) - pow(a,2) );

		glm::vec2 p2(m_position.x + a*(p1.x-m_position.x)/d,m_position.y + a*(p1.y-m_position.y)/d);

		glm::vec2 i1(p2.x+h*(p1.y - m_position.y)/d,p2.y-h*(p1.x-m_position.x)/d);
		glm::vec2 i2(p2.x-h*(p1.y-m_position.y)/d,p2.y+h*(p1.x-m_position.x)/d);

		temp.push_back(i1);
		temp.push_back(i2);
	}
	return temp;

}