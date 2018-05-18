#include "Game.h"
#include "TextureManager.h"
#include "Globals.h"
#include <iostream>
bool Game::init(const char* title, int xPos, int yPos, int height, int width, int flags)
{
	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) >= 0)
	{
		std::cout << "init success, creating window ..." << std::endl;
		// if we have succeeded, create the window
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, height, width, flags);

		// if the window creation succeeded create renderer
		if (m_pWindow != 0)
		{
			std::cout << "Window creation success.. creating renderer" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_pRenderer != 0)
			{
				std::cout << "Renderer creation success. Setting initial color" << std::endl;
				//SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
			}
			else
			{
				std::cout << "Renderer creation failed, aborting" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "Window creation failed, aborting." << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "ERROR: Failed to initialise SDL, aborting..." << std::endl;
		return false; // SDL couldn't init.
	}

	std::cout << "Running game..." << std::endl;
	m_bRunning = true;

	// Test loading textures
	std::cout << "Running test load of texture" << std::endl;

	if (!TheTextureManager::Instance()->load("data/Player.bmp", "player", m_pRenderer))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("data/Mushroom1.bmp", "mushroom", m_pRenderer))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("data/Head.bmp", "head", m_pRenderer))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("data/Body.bmp", "segment", m_pRenderer))
	{
		return false;
	}

	// Test game object classes
	m_Player.load(0, 0, 16, 16, "player");

	// Test grid
	Grid* g = new Grid(30, 30);
	m_Grid = g;
	m_Grid->GenerateGrid();
	m_Grid->ClearGrid();
	m_Grid->PlaceMushrooms(Shrooms, 15);

	//Test Centipede
	int startX = gGameStrtAreaX;
	int startY = gGameStartAreaY;
	Centipede c = Centipede();
	c.load(startX, startY, gCellSize, gCellSize, "head");
	c.Init();
	Centipedes.push_back(c);
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	//render the gameObjects

	m_Player.draw(m_pRenderer);
	for (int i = 0; i < 15; ++i)
	{
		Shrooms[i].draw(m_pRenderer);
	}

	for (std::vector<Centipede>::iterator it = Centipedes.begin(); it != Centipedes.end(); ++it)
	{
		it->draw(m_pRenderer);
	}

	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	std::cout << "Cleaning game..." << std::endl;
	m_Player.clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_MOUSEMOTION:
			m_Player.currentPosX = event.motion.x;
			m_Player.currentPosY = event.motion.y;
			break;
		default:
			break;
		}
	}
}

void Game::update(Uint32 Ticks)
{
	// update player objects

	

	m_Player.update(Ticks);
	for (std::vector<Centipede>::iterator it = Centipedes.begin(); it != Centipedes.end(); ++it)
	{
		it->update(Ticks);
	}
}