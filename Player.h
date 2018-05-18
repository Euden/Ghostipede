#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include <iostream>

class Player : public GameObject
{
public:

	void load(int x, int y, int wiTicksh, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update(Uint32 Ticks);
	void clean();

	int currentPosX, currentPosY;
};
#endif
