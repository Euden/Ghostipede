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
	void Init(std::vector<Segment>& tailSegments, uint32_t GameTimeMs);
	void load(int x, int y, int width, int height, std::string textureID);
	void draw(SDL_Renderer* pRenderer);
	void update(Uint32 Ticks);
	void clean();

	void collision();
	void SetMushrooms(std::vector<Mushroom>& shrooms);
	int currentPosX, currentPosY;

	std::vector<Segment>& GetSegments() { return segments; }

	Segment* splitSegment = nullptr;
	Segment* headSegment = nullptr;

	int segmentHitIndex = 0;
	bool shouldSplit = false;
	bool isDead = false;
	int centipedeIndex = 0;
	uint32_t UpdateMs;

	CentipedeState currentState;
	CentipedeState previousState;
private:
	std::vector<Segment> segments;
	

	// time.
	int moveCount;
	int level;

	std::list<Vector2> PreviousPositions;
	std::vector<Mushroom>* Mushrooms;
};

#endif
