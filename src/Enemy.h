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

private:
	GLuint texture;
};

