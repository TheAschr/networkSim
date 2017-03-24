//Vertex Shader
#version 330 core
  
layout (location = 0) in vec2 position;


out vec4 vertexColor;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    vertexColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

}