#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

using namespace std;

class GameDisplay
{
public:
	GameDisplay();
	~GameDisplay();
	void initializeGameDisplay();
	void swapBuffer();

	SDL_GLContext glContext;

	void ResetDisplay(float r, float g, float b, float alpha);

	float GetScreenWidth() { return _screenWidth; };
	float GetScreenHeight() { return _screenHeight; };



private:

	void returnError(std::string errorString);
	float _screenWidth;
	float _screenHeight;
	SDL_Window* _window;




};

