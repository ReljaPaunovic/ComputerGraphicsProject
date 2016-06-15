#pragma once
#include "GameObject.h"

class BossSegment:
	public GameObject
{
public:
	BossSegment(BossSegment* obj, float x, float y, int i);
	~BossSegment();

	void tick(float deltaTime);
	void render();
	void onCollide(GameObject* other);

private:
	BossSegment* previousSegment;
	int segmentNum;
	float xDirection;
	float yDirection;

	float speed;

	float size;
	
};

