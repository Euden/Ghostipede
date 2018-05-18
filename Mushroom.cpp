#include "Mushroom.h"
#include <SDL.h>

void Mushroom::load(int x, int y, int wiTicksh, int height, std::string textureID)
{
	// Load each mushroom stage.
	GameObject::load(x, y, wiTicksh, height, textureID);
}

void Mushroom::draw(SDL_Renderer* pRenderer)
{
	// Only draw what stage we are.
	GameObject::draw(pRenderer);
}

void Mushroom::update()
{

}

void Mushroom::clean()
{
	GameObject::clean();
}