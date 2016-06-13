#include "Camera.h"

void Camera::setProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(x, x + width, y + height, y);
	glOrtho(x, x + width, y + height, y, -100, 100);
}

void Camera::updatePosition(Player* player) {

	//printf("angle = %f \n", player->angle);
	if (player->angle <= 180)
		x = player->x - width / 4 - width / 2 * player->angle / 180;
	else
		x = player->x - 3 * width / 4 + width / 2 * (player->angle - 180) / 180;
	y = player->y - height / 2;
	
}

float Camera::getX() const {
	return x;
}

float Camera::getY() const {
	return y;
}