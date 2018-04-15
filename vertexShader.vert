#version 130

in vec3 vertexPosition_modelspace;
in vec3 vertexcolor;

out vec3 position;
out vec3 fragmentcolor;

uniform mat4 MVP;

void main(){
    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
    position = vertexPosition_modelspace;
    fragmentcolor = vertexcolor;
}