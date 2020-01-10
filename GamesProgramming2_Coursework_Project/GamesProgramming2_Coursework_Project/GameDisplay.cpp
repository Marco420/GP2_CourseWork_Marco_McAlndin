#include "stdafx.h"
#include "GameDisplay.h"


GameDisplay::GameDisplay()
{
	_window = nullptr;
	//Set game window variables to desired 
	_screenHeight = 768.0f;
	_screenWidth = 1024.0f;
}


GameDisplay::~GameDisplay()
{
	//Delete our context, window and quit application
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

//Check for error, if occurs quit aplication
void GameDisplay::returnError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void GameDisplay::swapBuffer()
{
	//Swap buffers
	SDL_GL_SwapWindow(_window);
}

void GameDisplay::initializeGameDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	//Set bit of RGBS to display on screen
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); 
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	//Double buffer set up
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 

	//Create our Game window giving desired name and size
	_window = SDL_CreateWindow("GP2_Marco_McAlindin", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,(int)_screenWidth,(int)_screenHeight, SDL_WINDOW_OPENGL);
	//Check if window is created, if not return error
	if (_window == nullptr) { returnError("window failed to create"); }

	//Create GL context
	glContext = SDL_GL_CreateContext(_window);
	//Check if context is created, if not return error
	if (glContext == nullptr) { returnError("SDL Context failed to create"); }

	//Init GLEW
	GLenum glew = glewInit();
	//Check if glew initiated, if not return error
	if (glew != GLEW_OK) { returnError("GLEW failed to initialise"); }

	//enable z
	glEnable(GL_DEPTH_TEST);  
	//Enable function to not draw faces not pointed at camera
	glEnable(GL_CULL_FACE);

	
}

void GameDisplay::ResetDisplay(float r, float g, float b, float alpha)
{
	//Clear screen display
	glClearColor(r,g,b,alpha);
	//Clear buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
