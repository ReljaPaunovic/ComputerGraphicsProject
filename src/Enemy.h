#pragma once
#include "GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy();
	~Enemy();

	void tick(float deltaTime);
	void render();
	void onCollide(GameObject* other);

	void setHealth(float value) {
		health = value;
	}
	float getHealth() {
		return health;
	}
	void animateDeath();

private:
	float health = 10;
	GLuint texture;
};

