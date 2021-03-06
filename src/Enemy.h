#pragma once
#include "GameObject.h"
#include "OBJModel.h"
class Enemy :
	public GameObject
{
public:
	Enemy();
	~Enemy();

	void tick(float deltaTime);
	void render(bool shadow);
	void onCollide(GameObject* other);

	void setHealth(float value) {
		health = value;
	}
	float getHealth() {
		return health;
	}
private:
	float z;
	float health = 5;

	float spin = 0.0f;
	float spinRate;
};

