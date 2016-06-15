#include "Camera.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

void Camera::setProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x, x + width, y + height, y, -3000, 3000);
}

const float cameraAngle = -45.0f;

void Camera::setLightProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef(cameraAngle, 1, 0, 0);
	glOrtho(x, x + width, y + height, y, -3000, 3000);
}

glm::mat4 Camera::getLightProjection() {
	glm::mat4 projection = glm::ortho(x, x + width, y + height, y, -3000.f, 3000.f);
	glm::mat4 view = glm::rotate(glm::mat4(), glm::radians(cameraAngle), glm::vec3(1.f, 0.f, 0.f));

	return view * projection;
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