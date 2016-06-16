#pragma once
#include "GameObject.h"

class BossSegment:
	public GameObject
{
public:
	BossSegment(BossSegment* obj, float x, float y, int i);
	~BossSegment();

	void tick(float deltaTime);
	void render(bool shadow);
	void onCollide(GameObject* other);
	void animateDeath();

private:
	BossSegment* previousSegment;
	BossSegment* nextSegment;

	int segmentNum;
	float xDirection;
	float yDirection;

	float speed;

	float size;
	
};

