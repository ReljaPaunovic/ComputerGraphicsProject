#pragma once

#include <GL/freeglut.h>
#include "Collider.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void render() = 0;
	virtual void tick(float deltaTime) = 0;
	virtual void onCollide(GameObject* other) = 0;

	void setupTransformation() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef((float) x, (float) y, 0.0f);
		glRotatef((float) angle, 0.0f, 0.0f, 1.0f);
		glTranslatef((float) -cx, (float) -cy, 0.0f);
	}
	
	float x = 0, y = 0;

	// Center of object
	float cx = 0, cy = 0;

	float angle = 0;
	
	Collider* collider;
};

