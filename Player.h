#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"
#include "Bullet.h"
#include <iostream>
#include <vector>

class Player : public GameObject
{
public:

	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update(Uint32 Ticks);
	void clean();

	void SetPosition(int x, int y);
	void Fire();

	int currentPosX, currentPosY;
	bool bHasFired = false;
	Bullet* currentBullet = nullptr;
	std::vector<Mushroom>* Shrooms;
};
#endif
