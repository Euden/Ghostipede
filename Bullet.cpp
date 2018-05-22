#include "Bullet.h"
#include "Globals.h"

void Bullet::load(int x, int y, int width, int height, std::string textureID)
{
	GameObject::load(x, y, width, height, textureID);
}

void Bullet::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Bullet::update(Uint32 Ticks)
{
	float vel = gBulletSpeed;

	currentPosY = m_y - gCellSize;
	GameObject::update(currentPosX, currentPosY, Ticks);

	if (currentPosY < 0)
	{
		isDirty = true;
	}

	// Check for collision with a shroom
	for (std::vector<Mushroom>::iterator it = Shrooms->begin(); it != Shrooms->end(); ++it)
	{
		const SDL_Rect shroomBounds = it->GetBounds();
		const SDL_Rect currentBounds = GameObject::GetBounds();
		if (GameObject::checkCollision(currentBounds, shroomBounds))
		{
			if (it->lives > 0)
			{
				it->hit();
				isDirty = true;
			}
		}
	}
}

void Bullet::SetPosition(int x, int y)
{
	currentPosX = x;
	currentPosY = y;
}

void Bullet::clean()
{
	GameObject::clean();
}