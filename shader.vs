//Vertex Shader
#version 330 core
  
layout (location = 0) in vec2 position;


uniform vec4 vColor;

out vec4 inColor;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    inColor = vec4(vColor);

}