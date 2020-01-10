#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <string>
#include"Texture.h"

//Game transfor coo
Transform transform;

Game::Game()
{
	//Set gamestate to PLAY
	mainGameState = GameState::PLAY;

	//Create new display obj
	GameDisplay*  gameDisplay = new GameDisplay();
	//Create audio device obj
	GameAudio* audioDevice();


}


Game::~Game()
{
}

void Game::Run()
{
	//Initialize game systems
	InitializeSystems();
	//Game Loop
	MainGameLoop();
}

void Game::InitializeSystems()
{
	//Prepare display for game
	gameDisplay.initializeGameDisplay();

	//Load 3D models for game
	//Dinosaurs
	dinoModel1.LoadModel("..\\res\\DEINONYC.obj");
	dinoModel2.LoadModel("..\\res\\DEINONYC.obj");
	//Drone
	droneModel.LoadModel("..\\res\\drone.obj");
	//Ground
	ground.LoadModel("..\\res\\ground.obj");

	//Load game sounds
	heliSound = audioDevice.loadSound("..\\res\\HelicopterSound.wav");
	dinoSound = audioDevice.loadSound("..\\res\\dinoRoar.wav");

	//Initialize main camera for game
	mainCamera.InitializeCamera(glm::vec3(0, 0, -6), 70.0f, (float)gameDisplay.GetScreenWidth() / gameDisplay.GetScreenHeight(), 0.01f, 1000.0f);

	


}

void Game::MainGameLoop()
{
	//Execute game code while game is in PLAY State
	while (mainGameState != GameState::EXIT)
	{
		//Process game input
		Input();
		//Draw game on screen
		DrawGame();

		//Check if dinosaur gameObj collide, if so play "roar" sound
		if (CollisionDetection(dinoModel1.GetSpherePos(), dinoModel1.GetSphereRadius(), dinoModel2.GetSpherePos(), dinoModel2.GetSphereRadius())) AudioPlay(dinoSound,glm::vec3(0.0f,0.0f,0.0f));

		//Play audio
		AudioPlay(heliSound, glm::vec3(0.0f,0.0f,5.0f));
	}
}

void Game::Input()
{
	//Init SDL event
	SDL_Event evnt;

	//Process events when they occur
	while (SDL_PollEvent(&evnt) != 0) 
	{
		//Switch statement for every event 
		switch (evnt.type)
		{
		case SDL_QUIT:
			mainGameState = GameState::EXIT;
			break;
		}
	}
}

void Game::DrawGame()
{
	//Set Display RGBA
	gameDisplay.ResetDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	//Set shader
	Shader shader("..\\res\\shader"); //new shader
	//Load needed textures
	Texture dinoTexture("..\\res\\skin.jpg");
	Texture droneTexture("..\\res\\drone.jpg");
	Texture groundTexture("..\\res\\ground.jpg");

	/*======================================
			DINO MODEL DRAW STATS
	=======================================*/
	//DINO #1
	//Set position, rotation and scale for dino model
	transform.SetPos(glm::vec3(sinf(dinoSpeed) * 4, -2, 0.0));
	transform.SetRot(glm::vec3(0.0, cosf(dinoSpeed) * 2, 0));
	transform.SetScale(glm::vec3(1, 1, 1));

	//bind appropriate shader
	shader.Bind();
	//update shader
	shader.Update(transform, mainCamera);
	//Bind texture to model
	dinoTexture.Bind(0);
	//Draw dino model
	dinoModel1.Draw();
	//Update Coliision sphere with model pos, choosing sphere radius
	dinoModel1.UpdateSphere(*transform.GetPos(), 1.0f);

	//DINO #2
	//Set position, rotation and scale for dino model
	transform.SetPos(glm::vec3(sinf(-dinoSpeed) * 4, -2, 0.0));
	transform.SetRot(glm::vec3(0.0, cosf(dinoSpeed) * -2, 0));
	transform.SetScale(glm::vec3(1, 1, 1));

	//bind appropriate shader
	shader.Bind();
	//Update Shader
	shader.Update(transform, mainCamera);
	//Bind texture to model
	dinoTexture.Bind(0);
	//Draw dino model
	dinoModel2.Draw();
	//Update collision sphere pos
	dinoModel2.UpdateSphere(*transform.GetPos(), 1.0f);

	//Increase dino speed variable
	dinoSpeed +=0.1f;

	/*================================
			DRONE STATS		
	=================================*/

	transform.SetPos(glm::vec3(cosf(heliSpeed) * 6, 2, cosf(heliSpeed) * 20));
	transform.SetRot(glm::vec3(0.0, heliSpeed  * 10, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shader.Bind();
	shader.Update(transform, mainCamera);
	droneTexture.Bind(0);
	droneModel.Draw();

	/*================================
			HELICOPTER STATS
	=================================*/
	transform.SetPos(glm::vec3(cosf(heliSpeed) * 50, 2, sinf(heliSpeed) + 40));
	transform.SetRot(glm::vec3(0.0, heliSpeed * 5, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shader.Bind();
	shader.Update(transform, mainCamera);
	droneTexture.Bind(0);
	droneModel.Draw();

	/*================================
			GROUND STATS
	=================================*/
	transform.SetPos(glm::vec3(10, -80, 200));
	transform.SetRot(glm::vec3(80,0.0, 0.0));
	transform.SetScale(glm::vec3(1.2, 0.3, 0.5));

	shader.Bind();
	shader.Update(transform, mainCamera);
	groundTexture.Bind(0);
	ground.Draw();

	heliSpeed = heliSpeed + 0.1f;
	

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	//Swap buffers
	gameDisplay.swapBuffer();

}

bool Game::CollisionDetection(glm::vec3 pos1, float rad1, glm::vec3 pos2, float rad2)
{
	//calculate distance between two pheres
	float distance = glm::sqrt((pos2.x - pos1.x)*(pos2.x - pos1.x) + (pos2.y - pos1.y)*(pos2.y - pos1.y) + (pos2.z - pos1.z)*(pos2.z - pos1.z));

	//Check if distance is smaller than sum of radiuses
	if (distance < (rad1 + rad2))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Game::AudioPlay(unsigned int source, glm::vec3 pos)
{
	//Audio state
	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	if (AL_PLAYING != state)
	{
		audioDevice.playSound(source, pos);
	}
}