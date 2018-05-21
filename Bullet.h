#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameObject.h"
#include "Mushroom.h"
#include <vector>

class Bullet : public GameObject
{
public:

	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update(Uint32 Ticks);
	void clean();

	void SetPosition(int x, int y);

	bool isDirty = false;
	int currentPosX, currentPosY;

	std::vector<Mushroom>* Shrooms;
};

#endif

