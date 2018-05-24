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
	// Check for shroom collision, stay where you are if so.
	for (std::vector<Mushroom>::iterator it = Shrooms->begin(); it != Shrooms->end(); ++it)
	{
		const SDL_Rect* shroomBounds = &it->GetBounds();
		const SDL_Rect* playerBounds = &GameObject::GetBounds();
		SDL_Rect* intersection = new SDL_Rect();
		if (SDL_IntersectRect(playerBounds, shroomBounds, intersection))
		{
			currentPosX = oldPosX;// -= currentPosX + m_width - shroomBounds->x;
		}
	}

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

	oldPosX = currentPosX;
	oldPosY = currentPosY;

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