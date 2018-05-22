#include "Bullet.h"
#include "Globals.h"
#include "Segment.h"

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

	// Check for collision with centipede.
	Centipede *hitCentipede = nullptr;
	Segment *hitSegment = nullptr;
	int hitSegmentNum = 0;
	for (std::vector<Centipede>::iterator c_it = m_Centipedes->begin(); c_it != m_Centipedes->end(); ++c_it)
	{
		for (std::vector<Segment>::iterator s_it = c_it->GetSegments().begin(); s_it != c_it->GetSegments().end(); ++s_it)
		{
			const SDL_Rect segmentBounds = s_it->GetBounds();
			// sort out catepillar bounds
			const SDL_Rect currentBounds = GameObject::GetBounds();
			if (GameObject::checkCollision(currentBounds, segmentBounds))
			{
				isDirty = true;
				hitCentipede = &(*c_it);
				hitSegment = &(*s_it);
				c_it->segmentHitIndex = hitSegmentNum;
				break;
			}
			++hitSegmentNum;
		}
	}

	if (hitCentipede != nullptr && hitSegment != nullptr)
	{
		hitCentipede->shouldSplit = true;
		hitCentipede->splitSegment = hitSegment;
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