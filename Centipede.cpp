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


void Centipede::update(Uint32 Ticks)
{
	int currentX = m_x;
	int currentY = m_y;

	switch (currentState) {
	case CSRight:
		// 1 
		if (m_x + gCellSize >= gGameWidth - gCellSize) {

			// 2
			if (m_y - gCellSize  == gGameStartAreaY) {
				previousState = CSUpLeft;
				currentState = CSRight;
			}
			else if (m_y == gGameStartAreaY + gGameHeight - gCellSize) {
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
		if (m_x  == gGameStrtAreaX) {

			if (m_y - gCellSize == gGameStartAreaY) {
				previousState = CSUpRight;
				currentState = CSLeft;
			}
			else if (m_y == gGameStartAreaY + gGameHeight) {
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
			currentPosY = m_y + gCellSize;
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
			currentPosY = m_y + gCellSize;
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

// 		if (PreviousPositions.size() > gCentipedeLength)
// 		{
// 			PreviousPositions.pop_back();
// 		}
// 		else
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