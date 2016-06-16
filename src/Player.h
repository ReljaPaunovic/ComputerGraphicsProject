#pragma once

#include "GameObject.h"
#include <GL/freeglut.h>

#define SFML_STATIC
#include <SFML/Audio.hpp>

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
	int killCount = 0;

private:
	float health = 100;

	float velocity = 0.0f;

	float accelerationForward = 0.0f;
	float accelerationBackward = 0.0f;
	
	float rotationLeft = 0.0f;
	float rotationRight = 0.0f;

	bool firing = false;
	float firingDelay = 1.0f / 2.0f; 
	float timeUntilNextFire = 0.0f;

	float upperBoundary = 500;
	float lowerBoundary = -650;

	float roll = 0.0f;
	float rollTarget = 0.0f;

	GLuint texture;
	GLuint textureNormal;
	GLuint shader;

	sf::SoundBuffer shootSoundBuffer;
	sf::Sound shootSound;
};

