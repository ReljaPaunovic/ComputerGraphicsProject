#pragma once

#include "Enemy.h"
#include "OBJModel.h"
#include "main.h"
#include "BossSegment.h"

class Boss :
	public GameObject
{
public:
	Boss() :
		modelHead("models/head.obj"),
		modelEye("models/eye.obj") {
		velocity = 400;
		collider = nullptr;
		numSegments = 32;
		loadTextures();
		firstTime = true;
		BossSegment* previous = nullptr;
		for (int i = 0; i < numSegments; i++) {
			BossSegment * bs = new BossSegment(previous, this->x, this->y, i);
			gameObjects.push_back(bs);
			previous = bs;
		}
	}

	~Boss();

	void loadTextures();

	void tick(float deltaTime);
	void render();
	void onCollide(GameObject* other);

private:
	OBJModel modelHead;
	OBJModel modelEye;

	GLuint eyeTexture;
	GLuint rivetTexture;

	float xDirection;
	float yDirection;

	float speed;
	float velocity;

	int  numSegments;
	bool firstTime;

	float previousX;
	float previousY;
};

