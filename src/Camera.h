#pragma once
#include "Player.h"
#include <glm/mat4x4.hpp>

class Camera {
public:
	Camera(int width, int height) : width(width), height(height) {}

	void updatePosition(Player* player);
	void setProjection();
	void setLightProjection();

	glm::mat4 getLightProjection();

	float getX() const;
	float getY() const;

private:
	float x = 0, y = 0;
	int width, height;
};