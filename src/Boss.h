#pragma once

#include "Enemy.h"
#include "OBJModel.h"

class Boss :
	public GameObject
{
public:
	Boss() : modelBody("models/head.obj") {
		collider = nullptr;
	}

	~Boss();

	void tick(float deltaTime);
	void render();
	void onCollide(GameObject* other);

private:
	OBJModel modelBody;
};

