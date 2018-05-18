#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Game.h"
#include "Globals.h"

Game* game = 0;


int main()
{
	game = new Game();

	if (game->init("Ghostipede", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 30 * 16, 30 * 16, 0))
	{
		SDL_ShowCursor(SDL_DISABLE);

		
		// Main game loop.
		uint32_t GameTimeMs = SDL_GetTicks();
		while (game->running())
		{
			//... Do work
			game->handleEvents();
			game->update(GameTimeMs);
			game->render();

			GameTimeMs = SDL_GetTicks();
		}

		game->clean();
		return 0;
	}
	
	return 1;
}