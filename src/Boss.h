#pragma once

#include "Enemy.h"
#include "OBJModel.h"

class Boss :
	public GameObject
{
public:
	Boss() :
		modelHead("models/head.obj"),
		modelEye("models/eye.obj") {

		collider = nullptr;

		loadTextures();
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

	GLuint loadTexture(const std::string& filename);
};

