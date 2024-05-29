// Game engine.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "LabelManager.h"
#include "ButtonManager.h" // #include "ResourceManager.h"

#include <iostream>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	int init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();

	void clean();
	bool running();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;

	ResourceManager resourceManager;
	LabelManager labelManager;
	ButtonManager buttonManager;
};