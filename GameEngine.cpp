#include "GameEngine.h"

GameEngine::GameEngine() : resourceManager(), labelManager(), buttonManager() {
	window = nullptr;
	renderer = nullptr;
	isRunning = false;
}

GameEngine::~GameEngine() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

int GameEngine::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	SDL_LogInfo(0, "Application en cours d'initialisation...");

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	int flags = SDL_WINDOW_SHOWN;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur d'initialisation de SDL : %s", SDL_GetError());
		return 1;
	}
	
	if (TTF_Init() != 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de l'initialisation de SDL_ttf : %s", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la création de la fenêtre : %s", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur de la création du rendu : %s", SDL_GetError());
		return 1;
	}

	resourceManager.init(renderer);
	buttonManager.init(renderer, resourceManager);

	resourceManager.loadTexture("buttonHovered", "assets/cppHovered.png");
	resourceManager.loadTexture("buttonPressed", "assets/cppPressed.png");

	buttonManager.addButton("button",ButtonType::Image, "assets/cpp.png", { 0,0,256,256 }, { 0,0,256,256 });
	isRunning = true;
	SDL_LogInfo(0, "Application initialisée !");
	return 0;
}

void GameEngine::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
	buttonManager.handleEvents(event);
}
void GameEngine::update() {
	//
}
void GameEngine::render() {
	// Effacer l'écran
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	labelManager.renderLabels(renderer);
	buttonManager.renderButtons();

	// Actualiser l'écran
	SDL_RenderPresent(renderer);
}

void GameEngine::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}
bool GameEngine::running() {
	return isRunning;
}