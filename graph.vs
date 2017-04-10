//Vertex Shader
#version 330 core
  
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 colors;

uniform mat4 model;

out vec4 vertexColor;

void main()
{
    gl_Position = model * vec4(position.x, position.y, 0.0, 1.0);
    vertexColor = vec4(colors, 1.0f);

}
