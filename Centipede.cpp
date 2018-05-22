#include "Centipede.h"
#include "Globals.h"
#include <SDL.h>
#include <iostream>

void Centipede::Init()
{
	currentState = CSRight;
	previousState = CSDownRight;
	moveCount = 0;
	UpdateMs = MS_PER_UPDATE;
	if (gCentipedeLength > 0)
	{
		for (int i = 0; i < gCentipedeLength; ++i)
		{
			Segment segment = Segment();

			segments.push_back(segment);
		}

		Segment* parentSegment = &(segments[0]);

		for (std::vector<Segment>::iterator it = segments.begin(); it != segments.end(); ++it)
		{
			it->load(m_x + gCellSize, m_y, gCellSize, gCellSize, "segment");
			it->SetPosition(m_x + gCellSize, m_y);

			Vector2 v;
			v.x = m_x;
			v.y = m_y;

			PreviousPositions.emplace_front(v);
		}
	}
}

void Centipede::load(int x, int y, int width, int height, std::string textureID)
{
	// Load segments of the centipede.

	GameObject::load(x, y, width, height, textureID);
}

void Centipede::draw(SDL_Renderer* pRenderer)
{
	// Only draw what stage we are.
	GameObject::draw(pRenderer);

	for (std::vector<Segment>::iterator it = segments.begin(); it != segments.end(); ++it)
	{
		it->draw(pRenderer);
	}
}

void Centipede::SetMushrooms(std::vector<Mushroom>& shrooms)
{
	Mushrooms = &shrooms;
}

void Centipede::update(Uint32 Ticks)
{
	int currentX = m_x;
	int currentY = m_y;

	SDL_Rect centipedeBounds = GameObject::GetBounds();
	
	for (std::vector<Mushroom>::iterator it = Mushrooms->begin(); it != Mushrooms->end(); ++it)
	{
			SDL_Rect shroomBounds = it->GetBounds();

			if (currentState == CSRight) {
				SDL_Rect rightBounds = centipedeBounds;
				rightBounds.x = rightBounds.x + gCellSize;
				if (GameObject::checkCollision(rightBounds, shroomBounds)) {
					if (it->lives > 0)
					{
						collision();
					}
					break;
				}
			}

			// 4
			if (currentState == CSLeft) {
				SDL_Rect leftBounds = centipedeBounds;
				leftBounds.x = leftBounds.x - gCellSize;
				if (GameObject::checkCollision(leftBounds, shroomBounds)) {
					if (it->lives > 0)
					{
						collision();
					}
					break;
				}
			}
	}

	switch (currentState) {
	case CSRight:
		// 1 
		if (m_x + gCellSize >= gGameWidth + gCellSize) {

			// 2
			if (m_y + gCellSize >= gGameHeight) {
				previousState = CSUpLeft;
				currentState = CSRight;
			}
			else if (m_y <= 0) {
				// 3
				previousState = CSDownRight;
				currentState = CSRight;
			}
			else {
				// 4
				if (previousState == CSDownRight ||
					previousState == CSDownLeft) {
					currentState = CSDownLeft;
				}
				else {
					currentState = CSUpLeft;
				}
				previousState = CSRight;
				return;
			}
			// 5 
			collision();
		}
		else {
			// 6
			currentPosX = m_x + gCellSize;
		}

		break;
	case CSLeft:
		// Check for a wall collision
		if (m_x <= 0) {

			if (m_y + gCellSize >= gGameHeight) {
				previousState = CSUpRight;
				currentState = CSLeft;
			}
			else if (m_y <= 0) {
				// Top collision
				previousState = CSDownLeft;
				currentState = CSLeft;
			}
			else {
				// Left wall collision
				if (previousState == CSDownRight ||
					previousState == CSDownLeft) {
					currentState = CSDownRight;
				}
				else {
					currentState = CSUpRight;
				}
				previousState = CSLeft;
				return;
			}

			collision();
		}
		else {
			currentPosX = m_x - gCellSize;
		}

		break;
	case CSDownLeft:
		// 1
		if (moveCount == 0) {
			currentPosY = m_y + gCellSize;
			moveCount++;
		}
		else {
			// 2
			currentPosX = m_x - gCellSize;
			moveCount = 0;
			currentState = CSLeft;
			previousState = CSDownLeft;
		}

		break;
	case CSDownRight:
		if (moveCount == 0) {
			currentPosY = m_y + gCellSize;
			moveCount++;
		}
		else {
			currentPosX = m_x + gCellSize;
			moveCount = 0;
			currentState = CSRight;
			previousState = CSDownRight;
		}

		break;
	case CSUpRight:
		if (moveCount == 0) {
			currentPosY = m_y - gCellSize;
			moveCount++;
		}
		else {
			currentPosX = m_x + gCellSize;
			moveCount = 0;
			currentState = CSRight;
			previousState = CSUpRight;
		}

		break;
	case CSUpLeft:
		if (moveCount == 0) {
			currentPosY = m_y - gCellSize;
			moveCount++;
		}
		else {
			currentPosX = m_x - gCellSize;
			moveCount = 0;
			currentState = CSLeft;
			previousState = CSUpLeft;
		}

		break;
	default:
		break;
	}

	if (Ticks > UpdateMs)
	{
		UpdateMs += MS_PER_UPDATE;
		{
			Vector2 v;
			v.x = m_x;
			v.y = m_y;
			PreviousPositions.push_front(v);
			PreviousPositions.pop_back();
		}

		GameObject::update(currentPosX, currentPosY, Ticks);

		int i = 0;
		for (std::list<Vector2>::iterator it = PreviousPositions.begin(); it != PreviousPositions.end(); ++it)
		{
			if (i < gCentipedeLength)
			{
				segments[i].SetPosition(it->x, it->y);

				segments[i].update(Ticks);
			}
			++i;
		}
	}
}




void Centipede::collision()
{
	bool down = currentState == CSDownLeft ||
				currentState == CSDownRight ||
				previousState == CSDownLeft ||
				previousState == CSDownRight;

	previousState = currentState;

	if (down)
	{
		if (currentState == CSRight) {
			currentState = CSDownLeft;
		}
		else {
			currentState = CSDownRight;
		}
	}
	else {
		if (currentState == CSRight) {
			currentState = CSUpLeft;
		}
		else {
			currentState = CSUpRight;
		}
	}
}

void Centipede::clean()
{
	GameObject::clean();
}