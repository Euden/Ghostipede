#ifndef _CENTIPEDE_H_
#define _CENTIPEDE_H_

#include "GameObject.h"
#include "Segment.h"
#include <vector>
#include <list>

typedef enum CentipedeState 
{
	CSRight,
	CSLeft,
	CSUpLeft,
	CSUpRight,
	CSDownLeft,
	CSDownRight

} CentipedeState;

struct Vector2 {
	int x;
	int y;
};

class Centipede : public GameObject
{
public:

	void Init();
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update(Uint32 Ticks);
	void clean();

	void collision();

	int currentPosX, currentPosY;

private:
	std::vector<Segment> segments;
	CentipedeState currentState;
	CentipedeState previousState;

	// time.
	int moveCount;
	int level;
	uint32_t UpdateMs;

	std::list<Vector2> PreviousPositions;
};

#endif
