#pragma once
#include "GameObject.h"
class Projectile :
	public GameObject
{
public:
	Projectile(float x, float y, float direction, float velocity);
	~Projectile();

	void tick(float deltaTime);
	void render();
	void onCollide(GameObject* other);

	GLuint texture;

private:
	float velocity;
};
