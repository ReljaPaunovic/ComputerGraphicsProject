#pragma once

#include "GameObject.h"
#include <GL/freeglut.h>

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

	float getRotationLeft() {
		return rotationLeft;
	}
	float getRotationRight() {
		return rotationRight;
	}
	void setHealth(float value) {
		health = value;
	}
	float getHealth() {
		return health;
	}

private:
	float health = 80;

	float velocity = 0.0f;

	float accelerationForward = 0.0f;
	float accelerationBackward = 0.0f;
	
	float rotationLeft = 0.0f;
	float rotationRight = 0.0f;

	bool firing = false;
	float firingDelay = 1.0f / 10.0f;
	float timeUntilNextFire = 0.0f;

	float upperBoundary = 200;
	float lowerBoundary = -800;

	GLuint texture;
};

