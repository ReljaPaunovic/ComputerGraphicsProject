#include "Player.h"
#include "Util.h"
#include "Projectile.h"
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <stb_image.h>
#define PI 3.14



extern std::vector<GameObject*> gameObjects;

Player::Player()
{
	x = 100;
	y = 300;
	cx = 48;
	cy = 48;
	collider = new Collider(90,90);

	// Load and create texture
	int textureWidth, textureHeight;
	int textureComponents;
	stbi_uc* pixels = stbi_load("textures/spaceship.png", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(pixels);
}


Player::~Player()
{
}

float Player::getHealth() const {
	return health;
}

void Player::handleKeyboard(unsigned char key, bool down) {
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

int lastshot=999999;

void Player::tick(float deltaTime) {
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
	printf("angle = %g\n",angle);
	if (-y > upperBoundary) {
		if (angle <= 270 && angle >= 90)
			angle += (1 + y / upperBoundary);
		else
			angle -= (1 + y / upperBoundary);
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

	//if (other->)
		printf("Player -------> Enemy\n");
		//x -= cos(Util::deg2rad(angle));
		//y -= sin(Util::deg2rad(angle));
		velocity = 0;
}

void Player::render() {
	setupTransformation();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(0, 0);
		glTexCoord2f(0, 0);

		glVertex2f(96, 0);
		glTexCoord2f(1, 0);

		glVertex2f(96, 96);
		glTexCoord2f(1, 1);

		glVertex2f(0, 96);
		glTexCoord2f(0, 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// For testing purposes, collision circles
	/*glPushMatrix();
	glTranslatef((float)cx, (float)cy, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(-collider->width / 2, -collider->height / 2);
		glVertex2f(collider->width / 2, -collider->height / 2);
		glVertex2f(collider->width / 2, collider->height / 2);
		glVertex2f(-collider->width / 2, collider->height / 2);
	glEnd();
	glPopMatrix();*/

	// For testing purposes, collision circles
	glTranslatef((float)cx, (float)cy, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 300; i++) {
		double angletemp = 2 * PI * i / 300;
		double xtemp = cos(angletemp);
		double ytemp = sin(angletemp);
		glVertex2d(90 * xtemp, 90 * ytemp);
	}
	glEnd();
	// ******

	resetTransformation();
}
