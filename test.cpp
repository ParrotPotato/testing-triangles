#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <chrono>
#include <SOIL/SOIL.h>
#include <ctime>
#include <thread>

using namespace std;



GLfloat cudedata[] = {
        -1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f,-1.0f, 
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, 
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
};

GLfloat colordata[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};


GLuint LoadShader(const char* vertexShader, const char* fragmentShader);


int main(int argc,char **argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    int height = 400;
    int width = 600;
    SDL_Window* window = SDL_CreateWindow("Test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,400,SDL_WINDOW_OPENGL);
    bool windowRunning = true;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    
    GLenum erro = glewInit();
    glClearColor(0.0,0.3,0.5,1.0);

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f),(float)width/(float)height,0.1f,100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(4,3,3),
		glm::vec3(0,0,0),
		glm::vec3(0,1,0)
	);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * view * model ; 

    GLuint vertexArrayID ;
    glGenVertexArrays(2,&vertexArrayID);
    glBindVertexArray(vertexArrayID);

    GLuint vertexbuffer ;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(cudedata),cudedata,GL_STATIC_DRAW);
    
    GLuint colorbuffer;
    glGenBuffers(1,&colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colordata),colordata,GL_STATIC_DRAW);

    GLuint program = LoadShader("t_vertshader.vert","t_fragshader.frag");
    GLint matrixLocation = glGetUniformLocation(program,"MVP");
    
    SDL_Event event ; 
    while(windowRunning){
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);

        glUniformMatrix4fv(matrixLocation,1,GL_FALSE,&mvp[0][0]);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0
        );
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *)0
        );
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glUseProgram(0);

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    windowRunning = false;
                break;
            }
        }
        SDL_GL_SwapWindow(window);
    }
}

std::string loadFile(const char* filePath){
	std::string file_data ; 
	std::string line;
	ifstream file(filePath,std::ios::in);
	if(!file.is_open()){
		cout << "File : " << filePath << " unable to open " << endl;
		return "";
	}
	while(getline(file,line)){
		file_data += line + "\n";
	}
	file.close();
	return file_data;
}

GLuint compileShader(GLuint shaderID,const char* shader_source,const char* errorMessage){
	GLint result;
	int infoLenght;
	glShaderSource(shaderID,1,&shader_source,NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID,GL_COMPILE_STATUS,&result);
	glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH,&infoLenght);
	if(infoLenght > 0){
		std::vector<char> VertexShaderErrorMessage(infoLenght+1);
		glGetShaderInfoLog(shaderID, infoLenght, NULL, &VertexShaderErrorMessage[0]);
		cout << "Error  : " << errorMessage << endl;
		printf("		%s\n", &VertexShaderErrorMessage[0]);
		return (GLuint)0;
	}
	return (GLuint)1;
}

GLuint linkProgram(GLuint programID, GLuint vertexShader, GLuint fragmentShader){
	GLint result;
	int infoLenght;

	glAttachShader(programID,vertexShader);
	glAttachShader(programID,fragmentShader);
	glLinkProgram(programID);
	glGetProgramiv(programID,GL_LINK_STATUS,&result);
	glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&infoLenght);
	if(infoLenght > 0){
		std::vector<char> ProgramErrorMessage(infoLenght+1);
		glGetProgramInfoLog(programID, infoLenght, NULL, &ProgramErrorMessage[0]);
		cout << "Error : Linking Program " <<endl;
		printf("		%s\n", &ProgramErrorMessage[0]);
		return (GLuint)0;
	}
	return (GLuint)1;
}

GLuint LoadShader(const char* vertexFilePath,const char* fragmentFilePath){

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	string vertexShaderCode = loadFile(vertexFilePath);
	if(vertexShaderCode == ""){
		return 0;
	}
	string fragmentShaderCode = loadFile(fragmentFilePath);
	if(fragmentShaderCode == ""){
		return 0;
	}
	compileShader(vertexShaderID,vertexShaderCode.c_str(),"VertexShader failed to compile");
	compileShader(fragmentShaderID,fragmentShaderCode.c_str(),"FragmentShader failed to compile");

	GLuint program = glCreateProgram();
    
    glBindAttribLocation(program,0,"vertexposition");
    glBindAttribLocation(program,1,"vertexColor");

	linkProgram(program,vertexShaderID,fragmentShaderID);

	glDetachShader(program,vertexShaderID);
	glDetachShader(program,fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return program;
}
