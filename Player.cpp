#include "Player.h"
#include <SDL.h>

void Player::load(int x, int y, int wiTicksh, int height, std::string textureID)
{
	GameObject::load(x, y, wiTicksh, height, textureID);
}

void Player::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Player::update(Uint32 Ticks)
{
	GameObject::update(currentPosX, currentPosY, Ticks);
}

void Player::clean()
{
	GameObject::clean();
}