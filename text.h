//
//  text.h
//  Yarudake
//
//  Created by Alex Schrimpf on 2/20/17.
//  Copyright © 2017 Alex Schrimpf. All rights reserved.
//

#ifndef text_h
#define text_h

#include <stdio.h>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//#include "texture.h"
#include "shader.h"
#include "window.h"

const std::string FONT_FILE_LOCATION = "Arial.ttf";

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Horizontal offset to advance to next glyph
};

class Text{
public:
    Text(Shader* tShader);
    void render(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
    GLuint VAO,VBO, texture;
    Shader* shader;
};
#endif /* text_h */
