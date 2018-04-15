#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#define TIR 1 
#define QUAD 2 
using namespace std;

int main(int argc,char **argv){
    std::string filename;
    int flag = 0 ;
    int type = 0 ; 
    
    cout << "Enter the file name : " ;
    getline(cin,filename);
    cin.ignore();
    
    cout << "Follow Concatination : " ;
    cin >> flag;
    cin.ignore();
    if(flag == 1 ){
        cout << "Type : " ;
        cin >> type ; 
    }
    
    ofstream file;
    file.open(filename.c_str());

    SDL_Init(SDL_INIT_EVERYTHING);
	bool isClosed = true;
	cout << "	Creating Window " << endl;
	SDL_Window * window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,400,SDL_WINDOW_OPENGL);
	isClosed = false;
	if(window == NULL){
		cout << "		Window Creation failed !! " << endl;
		return 0;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	cout << "	Creating context " << endl;
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
    int counter  = 0 ; 
    SDL_Event event ; 
    while(isClosed == false){
        SDL_GL_SwapWindow(window);
        glClear(GL_COLOR_BUFFER_BIT);

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isClosed = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    counter++;
                    cout << "Stroing value : " << event.motion.x << ',' << event.motion.y << endl;
                    file << event.motion.x << ' ' << event.motion.y  << ' ' << 0  << endl;
                    break;
            }
        }
    }

    file.close();
    cout << "	Deleting Context " << endl;
	SDL_GL_DeleteContext(context);
	cout << "	Deleting window " << endl;
	SDL_DestroyWindow(window);
	SDL_Quit();
	cout << "	Exiting Main" << endl;
	return 0;
}