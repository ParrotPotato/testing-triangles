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

//Triangle Coordinates ///
/*
static const GLfloat data[] = {
	//first triangle 
	600.0f,400.0f,0.0f,
	600.0f,00.0f,0.0f,
	00.0f,000.0f,0.0f,

	//second triangle 
	600.0f,400.0f,0.0f,
	00.0f,400.0f,0.0f,
	00.0f,000.0f,0.0f,

};

*/

static const GLfloat data[] = {
	//first triangle 
	150.0f,100.0f,0.0f,
	450.0f,300.0f,0.0f,
	150.0f,300.0f,0.0f,

	//second triangle 
	150.0f,100.0f,0.0f,
	450.0f,300.0f,0.0f,
	450.0f,100.0f,0.0f,

};

int PROGRAMM_RUNNING = 1 ; 
int condition_value = 1;
GLuint LoadShader(const char* vertexFilePath,const char* fragmentFilePath);
float map(float u1,float l1,float u2,float l2,bool indirection,float value);
GLuint createVertexArrayID();
void getValue();

int main(int argc,char **argv){

	auto date_time = std::chrono::system_clock::now();
	std::time_t startTime = std::chrono::system_clock::to_time_t(date_time);
	cout << "\nRunning ./window at \nStart Time :" << std::ctime(&startTime) << endl;
	//giving the triangle the normalised coordinates 
	GLfloat triangle[18];
	triangle[0] = 		map(1.0,-1.0,600.0,0.0,false,data[0]) ; 
	triangle[1] = 		map(1.0,-1.0,0.0,400.0,false,data[1]) ; 
	triangle[2] = 		0.0 ; 
	triangle[3] = 		map(1.0,-1.0,600.0,0.0,false,data[3]) ; 
	triangle[4] = 		map(1.0,-1.0,0.0,400.0,false,data[4]) ;
	triangle[5] = 		0.0 ; 
	triangle[6] = 		map(1.0,-1.0,600.0,0.0,false,data[6]) ; 
	triangle[7] = 		map(1.0,-1.0,0.0,400.0,false,data[7]) ; 
	triangle[8] = 		0.0 ; 
	triangle[9] = 		map(1.0,-1.0,600.0,0.0,false,data[9]) ; 
	triangle[10] = 		map(1.0,-1.0,0.0,400.0,false,data[10]) ; 
	triangle[11] = 		0.0 ; 
	triangle[12] = 		map(1.0,-1.0,600.0,0.0,false,data[12]) ; 
	triangle[13] = 		map(1.0,-1.0,0.0,400.0,false,data[13]) ;
	triangle[14] = 		0.0 ; 
	triangle[15] = 		map(1.0,-1.0,600.0,0.0,false,data[15]) ; 
	triangle[16] = 		map(1.0,-1.0,0.0,400.0,false,data[16]) ; 
	triangle[17] = 		0.0 ; 
	//cout << "triangle : " <<' ';
	//for(int i=0 ; i < 18 ; i++){
	//	if(i%3 == 0 && i!=0){
	//		cout << endl;
	//	}
	//	cout << triangle[i] << ' ' ; 
	//	
	//}
	//cout << endl;
	//creating window and initialising SDL, GLEW and GL libraries
	SDL_Init(SDL_INIT_EVERYTHING);
	bool isClosed = true;
	//cout << "	Creating Window " << endl;
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0,&DM);
	double width = DM.w/2;
	double height = DM.h/2;
	SDL_Window * window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,400,SDL_WINDOW_OPENGL);
	isClosed = false;
	if(window == NULL){
		cout << "		Window Creation failed !! " << endl;
		return 0;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	//cout << "	Creating context " << endl;
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if(context == NULL){
		cout << "		Context unable to initialise " << endl;
		return 0;
	}
	GLenum erro = glewInit();
	if(erro != GLEW_OK){
		cout << "	Glew unable to initialise " << endl;
		return 0;
	}
	//craeting a vertex array 
	GLuint vertexArrayID = createVertexArrayID();
	//creating a vertex buffer 
	GLuint vertexbuffer ;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(triangle),triangle,GL_STATIC_DRAW);

	//setting the default color of the window 
	//glClearColor(0.0,0.3,0.5,1.0);
	glClearColor(0.02,0.3,0.58,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	SDL_GL_SwapWindow(window);
	//cout << "	Window Created and Running Successfully "<<endl;
	SDL_Event event ;

	float timePassed = 0.0 ;
	float light_x = 0.0;
	float light_y = 0.0;
	int staticDrawingValue = 0 ; 
	///Creating projection matrices///
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f),(float)width/(float)height,0.1f,100.0f);
	glm::mat4 view = glm::lookAt(
		glm::vec3(4,3,3),
		glm::vec3(0,0,0),
		glm::vec3(0,1,0)
	);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * view * model ; 
	//////////////////////////////////
	GLuint program = LoadShader("vertexShader.vert","fragmentShader.frag");
	GLint time = glGetUniformLocation(program,"time");
	GLint lightPositionx = glGetUniformLocation(program,"lightPositionx");
	GLint lightPositiony = glGetUniformLocation(program,"lightPositiony");
	GLint condition = glGetUniformLocation(program,"condition");
	GLint staticDrawing = glGetUniformLocation(program,"staticDrawing");
	GLint MatrixID = glGetUniformLocation(program,"MVP");
	//getting the output mode of the variable 
	std:thread obtain_condition(getValue);
	obtain_condition.detach();
	//loading image and texture 

	////Main Loop ////
	while(isClosed==false){
		//cout << timePassed << endl;
		SDL_GL_SwapWindow(window);
		glClear(GL_COLOR_BUFFER_BIT);
		///Drawing triangles ///
		//-> selecting program to be used while drawing the triangles 
		
		glUseProgram(program);
		//drawing//

		//writing the uniform variable values in program (location,value)
		glUniform1f(time,timePassed);
		glUniform1f(lightPositionx,light_x);
		glUniform1f(lightPositiony,light_y);
		glUniform1i(condition,condition_value);
		glUniform1i(staticDrawing,staticDrawingValue);
		glUniformMatrix4fv(MatrixID,1,GL_FALSE,&mvp[0][0]);
		timePassed += 0.005 ;

		//drawing triangles 
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glVertexAttribPointer(
			0,			//consistency with the vertex shaders 
			3,			//size of the triangle (number of vertices )
			GL_FLOAT, 	//type
			GL_FALSE,	//normalised 
			0,			//stride
			(void*)0	//array buffer offest 
		);
		glDrawArrays(GL_TRIANGLES,0,6);
		glDisableVertexAttribArray(0);
		//diselecting any program that was selected ///
		glUseProgram(0);
		
		//////Event handeling /////
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					isClosed = true;
				break;
				case SDL_MOUSEMOTION:
					light_x =  map(1.0,-1.0,600.0,0.0,false,event.motion.x) ; 
					light_y =  map(1.0,-1.0,0.0,400.0,false,event.motion.y) ;
				break;
				//case SDL_MOUSEMOTION:
				//	cout << "Mouse Position Changed : " << endl;
				//	cout << "X = " << event.motion.x << " " << event.motion.y << endl;
				//break;
			}
		}
	}
//	cout << "	Deleting Context " << endl;
	SDL_GL_DeleteContext(context);
//	cout << "	Deleting window " << endl;
	SDL_DestroyWindow(window);
	SDL_Quit();
//	cout << "	Exiting Main" << endl;
	PROGRAMM_RUNNING = 0 ;
	if(obtain_condition.joinable() == true){
		obtain_condition.join();
	}
	startTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	cout << "\nFinish Time : " << std::ctime(&startTime) << endl;
	
	return 0;
}
//function for creating a vertexArray
GLuint createVertexArrayID(){
	GLuint vertexArrayID;
	glGenVertexArrays(1,&vertexArrayID);
	glBindVertexArray(vertexArrayID);
	return vertexArrayID;
}

//functions for loading, compiling and linking the shaders to a program and returning that program 
GLuint LoadShader(const char* vertexFilePath,const char* fragmentFilePath){
	//Creting shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	//reading files 
	string vertexShaderCode ;
	ifstream vertexShaderFile(vertexFilePath,std::ios::in);
	if(vertexShaderFile.is_open()){
		string line = "";
		while(getline(vertexShaderFile,line)){
			vertexShaderCode += "\n" + line;
		}
		vertexShaderFile.close();
	}
	else {
		cout << "	VertexFile unable to open ... " << endl;
		return 0;
	}
	//cout << "=========== VertexFileData ========" << vertexShaderCode << "\n==============================" <<endl;
	string fragmentShaderCode;
	ifstream fragmentShaderFile(fragmentFilePath,std::ios::in);
	if(fragmentShaderFile.is_open()){
		string line = "";
		while(getline(fragmentShaderFile,line)){
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderFile.close();
	}
	else {
		cout << "	FragmentFile unable to open ... " << endl;
		return 0;
	}
	//cout << "=========== FragmentFileData ========" << fragmentShaderCode << "\n==============================" <<endl;
	GLint result = GL_FALSE;
	int infoLogLenght;
	//compiliing shaders
//	cout << "	Compiling Shader : " << vertexFilePath << endl;
	const char* vertexData = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID,1,&vertexData,NULL);
	glCompileShader(vertexShaderID);
	////error checking code ////
	glGetShaderiv(vertexShaderID,GL_COMPILE_STATUS,&result);
	glGetShaderiv(vertexShaderID,GL_INFO_LOG_LENGTH,&infoLogLenght);
	if(infoLogLenght > 0){
		std::vector<char> VertexShaderErrorMessage(infoLogLenght+1);
		glGetShaderInfoLog(vertexShaderID, infoLogLenght, NULL, &VertexShaderErrorMessage[0]);
		cout << "Error : VertexShader" << vertexFilePath <<  endl;
		printf("		%s\n", &VertexShaderErrorMessage[0]);
	}
	////////////////////////////
	result = GL_FALSE;
	infoLogLenght = 0 ;
	////////////////////////////
//	cout << "	Compiling Shader : " << fragmentFilePath << endl;
	const char* fragmentData = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID,1,&fragmentData,NULL);
	glCompileShader(fragmentShaderID);
	///error checking code ////
	glGetShaderiv(fragmentShaderID,GL_COMPILE_STATUS,&result);
	glGetShaderiv(fragmentShaderID,GL_INFO_LOG_LENGTH,&infoLogLenght);
	if(infoLogLenght > 0){
		std::vector<char> FragmentShaderErrorMessage(infoLogLenght+1);
		glGetShaderInfoLog(fragmentShaderID, infoLogLenght, NULL, &FragmentShaderErrorMessage[0]);
		cout << "Error : FragmentShader -> " << fragmentFilePath << endl;
		printf("		%s\n", &FragmentShaderErrorMessage[0]);
	}

	////linking program ////
//	cout << "	Creating Shader program " << endl;
	GLuint program = glCreateProgram();
	glAttachShader(program,vertexShaderID);
	glAttachShader(program,fragmentShaderID);
//	cout << "	Attaching Shader program " << endl; 
	glLinkProgram(program);
	///error checking in linking /// 
	glGetProgramiv(program,GL_LINK_STATUS,&result);
	glGetProgramiv(program,GL_INFO_LOG_LENGTH,&infoLogLenght);
	if(infoLogLenght > 0){
		std::vector<char> ProgramErrorMessage(infoLogLenght+1);
		glGetProgramInfoLog(program, infoLogLenght, NULL, &ProgramErrorMessage[0]);
		cout << "Error : Linking Program " <<endl;
		printf("		%s\n", &ProgramErrorMessage[0]);
	}
//	cout << "	Deleting Shader Code " << endl;
	glDetachShader(program,vertexShaderID);
	glDetachShader(program,fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	//Testing the map functions 
	return program;
}
//function to map the absolute values of the triangle in the normalised coordinate system used by the OpenGL and the GPU 
float map(float u1,float l1,float u2,float l2,bool indirection,float value){
	if(indirection  == true ){
		///checking for out of bounds /// 
		if(u1 >= l1){
			if(value > u1 || value < l1){
				return 0.0;
			}
		}
		else if(u1 < l1){
			if(value > l1 || value < u1){
				return 0.0;
			}
		}
		float newValue = ((u2 - l2)/(u1 - l1))*(value - l1) + l2 ;
		return newValue;
	}
	else {
		///checking for out of bounds /// 
		if(u2 >= l2){
			if(value > u2 || value < l2){
				return 0.0;
			}
		}
		else if(u2 < l2){
			if(value > l2 || value < u2){
				return 0.0;
			}
		}
		float newValue = ((float)(u1 - l1)/(float)(u2 - l2))*(float)(value - l2) + l1 ;
		return newValue;
	}
}


void getValue(){
	while(PROGRAMM_RUNNING){
		if(PROGRAMM_RUNNING == 0){
			return ;
		}
		cout << "condition : " ; 
		cin >> condition_value ; 
		if(PROGRAMM_RUNNING == 0){
			return ;
		}
	}
}