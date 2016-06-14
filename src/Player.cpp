#include "Player.h"
#include "Util.h"
#include "Projectile.h"
#include <cmath>
#include <vector>
#include <stb_image.h>
#include "main.h"
#include <algorithm>
#define PI 3.14



Player::Player()
{
	x = 100;
	y = 400;
	cx = 48;
	cy = 48;
	collider = new Collider(35);
	velocity = 50;

	texture = Util::loadTexture("textures/spaceship.png");
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

	timeUntilNextFire -= deltaTime;
	if(firing && timeUntilNextFire <= 0.0f){
		timeUntilNextFire = firingDelay;
		float spawnX = x + cos(Util::deg2rad(angle)) * 48;
		float spawnY = y + sin(Util::deg2rad(angle)) * 48;
		gameObjects.push_back(new Projectile(spawnX, spawnY, angle, velocity + 100.0f));
	}
}

void Player::onCollide(GameObject* other) {
	// TODO
}

void Player::render() {
	setupTransformation();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 2);

		glTexCoord2f(1, 0);
		glVertex3f(96, 0, 2);

		glTexCoord2f(1, 1);
		glVertex3f(96, 96, 2);

		glTexCoord2f(0, 1);
		glVertex3f(0, 96, 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	resetTransformation();
}
