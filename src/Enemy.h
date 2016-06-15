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
	float z;
	float health = 10;

	float spin = 0.0f;
	float spinRate;

	OBJModel* model;
	GLuint texture;
	GLuint shader;
};

