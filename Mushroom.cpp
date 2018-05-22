#include "Mushroom.h"
#include <SDL.h>
#include <iostream>

void Mushroom::load(int x, int y, int wiTicksh, int height, std::string textureID)
{
	// Load each mushroom stage.
	GameObject::load(x, y, wiTicksh, height, textureID);

	lives = 3;
}

void Mushroom::draw(SDL_Renderer* pRenderer)
{
	// Only draw what stage we are.
	switch (lives)
	{
	case 0:
		break;
	case 1:
		m_textureID = "mushroom3";
		break;
	case 2:
		m_textureID = "mushroom2";
		break;
	case 3:
		m_textureID = "mushroom1";
		break;
	default:
		break;
	}
	if (lives > 0)
	{
		GameObject::draw(pRenderer);
	}
}

void Mushroom::hit()
{
	if (lives > 0)
	{
		lives -= 1;
		std::cout << "MUSHROOM LIVES: " << lives << std::endl;
	}
}

void Mushroom::update()
{

}

void Mushroom::clean()
{
	GameObject::clean();
}