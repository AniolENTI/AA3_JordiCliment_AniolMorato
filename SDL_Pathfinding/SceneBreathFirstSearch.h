#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "Grid.h"

class SceneBreathFirstSearch : 
public Scene
{
public:
	SceneBreathFirstSearch();
	~SceneBreathFirstSearch();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:
//Variables
	std::vector<Agent*> agents;
	std::vector<Vector2D> frontier;

	Vector2D coinPosition;
	Vector2D currentTarget;

	Grid* maze;
	bool draw_grid;

	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;

//Funcions
	void drawMaze();
	void drawCoin();
	bool loadTextures(char* filename_bg, char* filename_coin);
};

