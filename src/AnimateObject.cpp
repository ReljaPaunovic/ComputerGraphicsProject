#include "AnimateObject.h"
#include "main.h"
#include "Util.h"
#include "GameObject.h"
#include <algorithm>

AnimateObject::AnimateObject(float x, float y, float z)
{
	numSteps = 12;
	currentStep = 0;
	cx = 48;
	cy = 48;
	collider = new Collider(0);
	this->x = x;
	this->y = y;
	this->z = z;

	texture = Util::loadTexture("textures/Explosion.png");

	explosionSoundBuffer.loadFromFile("sounds/explosion.wav");
	explosionSound.setBuffer(explosionSoundBuffer);
	explosionSound.setVolume(100);

	explosionSound.play();
}


AnimateObject::~AnimateObject()
{
}

void AnimateObject::tick(float deltaTime)
{
	explosionRange = (1.0f - timeSoFar / (numSteps * StepDelay)) * 400.0f;
	explosionPos = glm::vec2(this->x, this->y);

	shockwaveRange = 50.0f;
	shockwaveDistance = timeSoFar / (numSteps * StepDelay) * 2000.0f;

	if (currentStep < numSteps) {
		timeUntilNextStep -= deltaTime;
		if (timeUntilNextStep <= 0.0f) {
			timeUntilNextStep = StepDelay;
			currentStep++;
		}
	}
	else {
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());

		explosionRange = 0.0f;
		shockwaveRange = 0.0f;
	}

	timeSoFar += deltaTime;
}

void AnimateObject::render()
{
	setupTransformation();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);

		glTexCoord2f((float)currentStep/numSteps , 0);
		glVertex3f(0, 0, z);

		glTexCoord2f((1 + (float)currentStep) / numSteps, 0);
		glVertex3f(96, 0, z);

		glTexCoord2f((1 + (float)currentStep) / numSteps, 1);
		glVertex3f(96, 96, z);

		glTexCoord2f((float)currentStep / numSteps, 1);
		glVertex3f(0, 96, z);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);

	resetTransformation();
}

void AnimateObject::onCollide(GameObject * other)
{
}
