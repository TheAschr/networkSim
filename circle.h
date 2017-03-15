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


const float INT_RAD = 0.005f;
const float INT_PRECISION = 10;
const float PI = 3.1415926f;

class Circle{
public:
    Circle(Shader& shader,glm::vec2& position, GLfloat radius,const int precision);
    virtual ~Circle(){
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }
    void draw(const glm::vec4& color);
    glm::vec2 getPos(){return m_position;}
    GLfloat getRad(){return m_radius;}
    std::vector<glm::vec2> getInts(Circle& circle);
private: 
    Shader* m_shader;
    glm::vec2 m_position;
    GLfloat m_radius;
    GLuint m_vbo,m_vao;
    int m_verts;
    int m_precision;
};

#endif