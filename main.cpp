// Game engine.cpp : définit le point d'entrée de l'application.
//
#define SDL_MAIN_HANDLED

#include "GameEngine.h"

int main()
{
	try
	{
		GameEngine GE;
		GE.init("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

		while (GE.running())
		{
			GE.handleEvents();
			GE.update();
			GE.render();
		}

		GE.clean();
	}
	catch (const std::exception& e)
	{
		std::cerr << "An exception occured:\n" << e.what() << "\n" << std::endl;
		return 1;
	}

	return 0;
}
