#include "GameObject.h"
#include "TextureManager.h"

void GameObject::load(int x, int y, int width, int height, std::string textureID)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_textureID = textureID;

	m_currentRow = 1;
	m_currentFrame = 1;
}

void GameObject::draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->draw(m_textureID, m_x, m_y, m_width, m_height, pRenderer);
}

void GameObject::update(int x, int y, Uint32 Ticks)
{
	m_x = x;
	m_y = y;
}

SDL_Rect GameObject::GetBounds()
{
	SDL_Rect bounds;
	bounds.h = m_height;
	bounds.w = m_width;
	bounds.x = m_x;
	bounds.y = m_y;

	return bounds;
}

void GameObject::clean()
{
	TextureManager::Instance()->clean(m_textureID);
}