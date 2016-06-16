#pragma once
#include "GameObject.h"

#define SFML_STATIC
#include <SFML/Audio.hpp>

class AnimateObject:
	public GameObject
{
public:
	AnimateObject(float x, float y, float z);
	~AnimateObject();

	void tick(float deltaTime);
	void render(bool shadow);
	void onCollide(GameObject* other);

private:
	int numSteps;
	int currentStep;

	float StepDelay = 1.0f / 10.0f;
	float timeUntilNextStep = 0.0f;
	float timeSoFar = 0.0f;

	float z;
	GLuint texture;

	sf::SoundBuffer explosionSoundBuffer;
	sf::Sound explosionSound;
};

