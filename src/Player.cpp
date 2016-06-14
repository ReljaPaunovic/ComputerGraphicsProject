#include "Player.h"
#include "Util.h"
#include "Projectile.h"
#include <cmath>
#include <vector>
#include <stb_image.h>
#include "main.h"
#include <algorithm>
#include "OBJModel.h"
#define PI 3.14



Player::Player()
{
	x = 100;
	y = 400;
	cx = 15;
	cy = 15;
	collider = new Collider(35);
	velocity = 50;

	texture = Util::loadTexture("textures/metal_plate.jpg");

	shader = Util::createShaderProgram("shaders/meshlighting.vert", "shaders/meshlighting.frag");
}


Player::~Player()
{
}

float Player::getHealth() const {
	return health;
}

void Player::handleKeyboard(unsigned char key, bool down) {
	// Do we need w and s?
	if (key == 'a') {
		rotationLeft = down ? 1.0f : 0.0f;
	} else if (key == 'd') {
		rotationRight = down ? 1.0f : 0.0f;
	} else if (key == 'w') {
		accelerationForward = down ? 1.0f : 0.0f;
	} else if (key == 's') {
		accelerationBackward = down ? 1.0f : 0.0f;
	} else if (key == ' ') {
		firing = down;
	}
}

void Player::tick(float deltaTime) {
	// Roll player to currently intended roll (based on turning or not)
	float deltaRoll = rollTarget - roll;
	roll += deltaRoll * deltaTime * velocity / 100.0f;

	rollTarget = 0.0f;
	if (rotationLeft) rollTarget += -15;
	if (rotationRight) rollTarget += 15;

	if (health <= 0)
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
	angle -= 180.0f * rotationLeft * deltaTime;
	angle += 180.0f * rotationRight * deltaTime;
	// To keep it in range (0, 359)
	if (angle < 0)
		angle += 360;
	if (angle >= 360)
		angle -= 360;

	velocity += accelerationForward;
	velocity -= accelerationBackward;

	x += cos(Util::deg2rad(angle)) * velocity * deltaTime;
	y += sin(Util::deg2rad(angle)) * velocity * deltaTime;
	//printf("angle = %g\n",angle);
	// Force player back down if he goes too far up
	if (-y > upperBoundary) {
		if (angle <= 270 && angle >= 90)
			angle += (1 + y / upperBoundary);
		else
			angle -= (1 + y / upperBoundary);
	}
	// Destroy if lower than lowerBoundary
	if (-y < lowerBoundary) {
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
	}

	// Should fire from two guns, but can't be bothered to set up the matrix for that right now
	timeUntilNextFire -= deltaTime;
	if(firing && timeUntilNextFire <= 0.0f){
		timeUntilNextFire = firingDelay;
		float spawnX = x + cos(Util::deg2rad(angle)) * 25;
		float spawnY = y + sin(Util::deg2rad(angle)) * 25;
		gameObjects.push_back(new Projectile(spawnX, spawnY, angle, velocity + 100.0f));
	}
}

void Player::onCollide(GameObject* other) {
	// TODO
}

void Player::render() {
	setupTransformation();

	glRotatef(roll, 1, 0, 0);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	GLint originalProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &originalProgram);
	glUseProgram(shader);

	static OBJModel lol("models/tiefighter.obj");
	lol.draw();

	glDisable(GL_TEXTURE_2D);

	glUseProgram(originalProgram);

	resetTransformation();
}
