#version 130
in vec3 vertexPosition_modelspace;
out vec3 position;

uniform mat4 MVP;

void main(){
    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
    position = vertexPosition_modelspace;
}