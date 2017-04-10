#ifndef circle_h
#define circle_h

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <cmath>

#include <iostream>

#include "shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

#include "window.h"

const GLfloat PI = 3.14159265358979f;

class Circle{
public:
    Circle(const glm::vec2& position,const GLfloat radius,const GLuint precision);
    ~Circle(){
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void draw(Shader& shader,const glm::vec4& color);

    glm::vec2 getPos() const {return m_position;}
    GLfloat getRad() const {return m_radius;}

    std::vector<glm::vec2> getIntersects(const Circle& circle) const ;

private: 
    glm::vec2 m_position;
    GLfloat m_radius;
    GLuint m_verts;
    GLuint m_vbo,m_vao;
};

#endif