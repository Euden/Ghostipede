#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include <SDL.h>
#include <string>

class GameObject
{
public:
	virtual void load(int x, int y, int width, int height, std::string textureID);
	virtual void draw(SDL_Renderer* pRenderer);
	virtual void update(int x, int y, Uint32 Ticks);
	virtual void clean();

	virtual SDL_Rect GetBounds();

protected:

	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;

	int m_x;
	int m_y;

	int m_width;
	int m_height;
};

#endif
