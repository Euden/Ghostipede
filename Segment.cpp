#include "Segment.h"

void Segment::load(int x, int y, int width, int height, std::string textureID)
{
	// Load each mushroom stage.
	GameObject::load(x, y, width, height, textureID);
}

void Segment::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Segment::SetPosition(int x, int y)
{
	m_CurrentPosX = x;
	m_CurrentPosY = y;
}

void Segment::update(Uint32 Ticks)
{
	GameObject::update(m_CurrentPosX, m_CurrentPosY, Ticks);
}