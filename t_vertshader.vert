#version 130

in vec3 vertexposition;
in vec3 vertexColor;

uniform mat4 MVP;

out vec3 fragmentColor;

void main(){
    gl_Position = MVP * vec4(vertexposition,1);
    fragmentColor = vertexColor;
}