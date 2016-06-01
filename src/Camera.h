#pragma once
#include "Player.h"

class Camera {
public:
	Camera(int width, int height) : width(width), height(height) {}

	void updatePosition(Player* player);
	void setProjection();

	float getX() const;
	float getY() const;

private:
	float x = 0, y = 0;
	int width, height;
};