#pragma once

#include "GameObject.h"
#include "Stopwatch.h"
#include <GL/GL.h>

class Player:
	public GameObject
{
public:
	Player();
	~Player();

	void handleKeyboard(unsigned char key, bool down);

	void tick(float deltaTime);
	void render();
	void onCollide(GameObject* other);

	float getHealth() const;

private:
	float health = 80;

	float velocity = 0.0f;

	float accelerationForward = 0.0f;
	float accelerationBackward = 0.0f;
	
	float rotationLeft = 0.0f;
	float rotationRight = 0.0f;

	bool firing = false;
	float firingDelay = 1.0f / 10;

	Stopwatch fireTimer;

	GLuint texture;
};

