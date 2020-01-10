#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GameDisplay.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "GameAudio.h"

enum class GameState { PLAY, EXIT };

class Game
{
public:
	Game();
	~Game();

	void Run();

private:

	//Private methods
	void InitializeSystems();
	void Input();
	void MainGameLoop();
	void DrawGame();
	void AudioPlay(unsigned int source, glm::vec3 pos);


	bool CollisionDetection(glm::vec3 pos1, float rad1, glm::vec3 pos2, float rad2);

	//Display object
	GameDisplay gameDisplay;
	//Gamestate enum
	GameState mainGameState;

	//audio device obj
	GameAudio audioDevice;

	//sound index var
	unsigned int heliSound;
	unsigned int dinoSound;



	//Main camera var
	Camera mainCamera;

	//Mesh of 3D models in game
	Mesh droneModel;
	Mesh dinoModel1;
	Mesh dinoModel2;
	Mesh ground;

	//speed/pos variables for gameObjects
	float heliSpeed;
	float dinoSpeed;
};



