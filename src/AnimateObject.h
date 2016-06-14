#pragma once
#include "GameObject.h"

class AnimateObject:
	public GameObject
{
public:
	AnimateObject(float x, float y);
	~AnimateObject();

	void tick(float deltaTime);
	void render();
	void onCollide(GameObject* other);

	int numSteps;
	int currentStep;

	float StepDelay = 1.0f / 10.0f;
	float timeUntilNextStep = 0.0f;

	GLuint texture;
};

