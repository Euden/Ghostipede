#ifndef _GAME_
#define _GAME_

#include <SDL.h>
#include <vector>
#include "Player.h"
#include "Grid.h"
#include "Mushroom.h"
#include "Centipede.h"

class Game
{
public:
	Game() {} // Default constructor.
	~Game() {} // Destructor.

	bool init(const char* title, int xPos, int yPos, int height, int width, int flags);

	void render();
	void update(Uint32 Ticks);
	void handleEvents();
	void clean();

	// Centipede specific functions
	void RemoveDeadCentipedes();

	bool running() { return m_bRunning; }


private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_currentFrame;

	bool m_bRunning;

	//GameObject m_go;
	Player m_Player;
	Grid* m_Grid;
	std::vector<Mushroom> Shrooms;
	std::vector<Centipede> Centipedes;
};

#endif // _GAME_