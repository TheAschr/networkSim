#ifndef text_h
#define text_h

#include <stdio.h>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "window.h"

const std::string FONT_FILE_LOCATION = "Arial.ttf";

struct Character {
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing; 
    GLuint Advance;
};

class Text{
public:
    Text(Shader* tShader);
    void render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_texture;
    Shader* m_shader;
};
#endif /* text_h */
