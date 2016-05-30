#pragma once
#include "Player.h"

class Camera {
public:
	Camera(int width, int height) : width(width), height(height) {}

	void updatePosition(Player* player);
	void setProjection();

private:
	int x = 0, y = 0;
	int width, height;
};