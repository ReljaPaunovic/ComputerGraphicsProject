#include "AnimateObject.h"
#include "main.h"
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

	int textureWidth, textureHeight;
	int textureComponents;
	stbi_uc* pixels = stbi_load("textures/Explosion.png", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(pixels);
}


AnimateObject::~AnimateObject()
{
}

void AnimateObject::tick(float deltaTime)
{
	if (currentStep < numSteps) {
		timeUntilNextStep -= deltaTime;
		if (timeUntilNextStep <= 0.0f) {
			timeUntilNextStep = StepDelay;
			currentStep++;
		}
	}
	else
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
}

void AnimateObject::render()
{
	setupTransformation();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

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

	glDisable(GL_TEXTURE_2D);

	resetTransformation();
}

void AnimateObject::onCollide(GameObject * other)
{
}
