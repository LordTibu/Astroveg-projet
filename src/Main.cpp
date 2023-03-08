#include "Game.h"


int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDel = 1000 / FPS;

	Uint32 frameStart;
	int frametime;

	Game* game;
	game = new Game("Astroveg", false);
	game->init();

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frametime = SDL_GetTicks() - frameStart;

		if (frameDel > frametime)
		{
			SDL_Delay(frameDel - frametime);
		}
	}

	game->clean();
	return 0;
}