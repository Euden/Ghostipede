#ifndef  _SEGMENT_H_
#define _SEGMENT_H_

#include "GameObject.h"
#include <SDL.h>
class Segment : public GameObject
{
public:
	void SetPosition(int x, int y);
	void load(int x, int y, int wiTicksh, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update(Uint32 Ticks);
	void clean() {};

	int m_PrevX, m_PrevY;
	int m_CurrentPosX, m_CurrentPosY;
	Segment* m_Parent;
};
#endif // ! _SEGMENT_H_

