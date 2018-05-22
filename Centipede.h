#ifndef _CENTIPEDE_H_
#define _CENTIPEDE_H_

#include "GameObject.h"
#include "Segment.h"
#include "Mushroom.h"
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

	void Init(std::vector<Segment>& tailSegments);
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update(Uint32 Ticks);
	void clean();

	void collision();
	void SetMushrooms(std::vector<Mushroom>& shrooms);
	int currentPosX, currentPosY;

	std::vector<Segment>& GetSegments() { return segments; }

	Segment* splitSegment = nullptr;
	int segmentHitIndex = 0;
	bool shouldSplit = false;
private:
	std::vector<Segment> segments;
	CentipedeState currentState;
	CentipedeState previousState;

	// time.
	int moveCount;
	int level;
	uint32_t UpdateMs;

	std::list<Vector2> PreviousPositions;
	std::vector<Mushroom>* Mushrooms;
};

#endif
