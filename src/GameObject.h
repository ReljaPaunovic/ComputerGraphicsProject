#pragma once

#include <GL/glew.h>
#include "Collider.h"
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera;

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void render() = 0;
	virtual void tick(float deltaTime) = 0;
	virtual void onCollide(GameObject* other) = 0;

	void setupTransformation();
	void resetTransformation();

	glm::vec2 getScreenPos(Camera* camera);

	float x = 0, y = 0;

	// Center of object
	float cx = 0, cy = 0;

	float angle = 0;
	
	Collider* collider;
};

