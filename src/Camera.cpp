#include "Camera.h"

void Camera::setProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(x, x + width, y + height, y);
}

void Camera::updatePosition(Player* player) {
	// TODO
}

float Camera::getX() const {
	return x;
}

float Camera::getY() const {
	return y;
}