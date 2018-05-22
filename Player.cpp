#include "Player.h"
#include "Globals.h"
#include <SDL.h>

void Player::load(int x, int y, int wiTicksh, int height, std::string textureID)
{
	GameObject::load(x, y, wiTicksh, height, textureID);
}

void Player::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
	
	if (currentBullet != nullptr)
	{
		currentBullet->draw(pRenderer);
	}
}

void Player::update(Uint32 Ticks)
{
	GameObject::update(currentPosX, currentPosY, Ticks);

	if (currentBullet != NULL)
	{
		currentBullet->update(Ticks);
		if (currentBullet->isDirty)
		{
			currentBullet = NULL;
		}
	}
}

void Player::SetPosition(int x, int y)
{
	if (y < gGameHeight - (4 * gCellSize)) {
		y = gGameHeight - (4 * gCellSize);
	}
		currentPosX = x;
		currentPosY = y;
}

void Player::Fire()
{
	if (currentBullet == NULL)
	{
		currentBullet = new Bullet();
		currentBullet->load(currentPosX, currentPosY, 1, gCellSize, "Bullet");
		currentBullet->SetPosition(currentPosX, currentPosY);
		currentBullet->Shrooms = Shrooms;
		currentBullet->m_Centipedes = m_Centipedes;
	}
	
}

void Player::clean()
{
	GameObject::clean();
}