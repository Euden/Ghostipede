#ifndef _MUSHROOM_H_
#define _MUSHROOM_H_

#include "GameObject.h"
#include <iostream>

class Mushroom : public GameObject
{
public:

	void load(int x, int y, int wiTicksh, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update();
	void clean();

	void hit();

	int lives;;
};
#endif
