#pragma once

#include "Enemy.h"
#include "OBJModel.h"
#include "main.h"
#include "BossSegment.h"
#include "Collider.h"
#include "Util.h"

class Boss :
	public GameObject
{
public:
	Boss() :
		modelHead("models/head.obj"),
		modelEye("models/eye.obj") {
		velocity = 1600;
		collider = new Collider(90);
		numSegments = 16;
		currentNumSegments = numSegments;
		loadTextures();
		firstTime = true;
		BossSegment* previous = nullptr;
		for (int i = 0; i < numSegments; i++) {
			BossSegment * bs = new BossSegment( previous, this->x, this->y, i);
			if (i == 0)
				tail = bs;
			gameObjects.push_back(bs);
			previous = bs;
		}
		if (shader == -1) {
			shader = Util::createShaderProgram("shaders/mesh.vert", "shaders/mesh.frag");
		}
	}

	~Boss();

	void loadTextures();

	void tick(float deltaTime);
	void render(bool shadow);
	void onCollide(GameObject* other);

	float getSpeed() {
		return speed;
	}
	BossSegment* getTail() {
		return tail;
	}
	void setTail(BossSegment* t) {
		tail = t;
	}
	int currentNumSegments;

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

	BossSegment* tail;
	GLint shader = -1;
};

