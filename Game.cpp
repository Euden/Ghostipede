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
	if (!TheTextureManager::Instance()->load("data/Mushroom2.bmp", "mushroom1", m_pRenderer))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("data/Mushroom3.bmp", "mushroom2", m_pRenderer))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("data/Mushroom4.bmp", "mushroom3", m_pRenderer))
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
	if (!TheTextureManager::Instance()->load("data/Laser.bmp", "Bullet", m_pRenderer))
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
	m_Grid->PlaceMushrooms(Shrooms, gNumOfShrooms);

	//Test Centipede
	int startX = gGameStrtAreaX;
	int startY = gGameStartAreaY;
	Centipede c = Centipede();
	c.load(startX, startY, gCellSize, gCellSize, "head");
	std::vector<Segment> s;
	c.Init(s);
	c.SetMushrooms(Shrooms);
	Centipedes.push_back(c);

	// Set player shrooms
	m_Player.Shrooms = &Shrooms;
	m_Player.m_Centipedes = &Centipedes;
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
			m_Player.SetPosition(event.motion.x, event.motion.y);
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_SPACE:
				m_Player.Fire();
				break;
			}
		default:
			break;
		}
	}
}

void Game::update(Uint32 Ticks)
{
	// update player objects

	

	m_Player.update(Ticks);

	Centipede* toSplitCheck = nullptr;
	for (std::vector<Centipede>::iterator it = Centipedes.begin(); it != Centipedes.end(); ++it)
	{
		it->update(Ticks);
		if (it->shouldSplit)
		{
			if ((it->segmentHitIndex < it->GetSegments().size() - 1))
			{
				// Create a new centipede. Set this segment to a mushroom. 
				//Set the next one along in the array to be the new tail end of the centipede.
				//Mushroom m = Mushroom();
				Segment* s = &it->GetSegments().at(it->segmentHitIndex);
				//Segment* nextSegment = &it->GetSegments().at(it->segmentHitIndex + 1);
				if (s != nullptr)
				{
					Centipede* newCentipede = new Centipede();
					newCentipede->load(s->m_CurrentPosX, s->m_CurrentPosY, gCellSize, gCellSize, "head");

					std::vector<Segment> newSegments;

					while (it->GetSegments().size() > it->segmentHitIndex)
					{
						newSegments.push_back(it->GetSegments().back());
						it->GetSegments().pop_back();
					}

					newCentipede->Init(newSegments, it->UpdateMs);
					newCentipede->SetMushrooms(Shrooms);
					toSplitCheck = newCentipede;
					it->shouldSplit = false;
				}
				else
				{
					it->GetSegments().pop_back();
				}
			}
		}
	}

	if (toSplitCheck)
	{
		Centipedes.push_back(*toSplitCheck);
		toSplitCheck = nullptr;
	}
}