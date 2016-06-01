#include "Player.h"
#include "Util.h"
#include <GL/GL.h>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Player::Player()
{
	x = 100;
	y = 300;
	cx = 48;
	cy = 48;
	//collider = new CircleCollider(5);

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
		velocity = 0.0f;
	}
}

void Player::tick(float deltaTime) {
	angle -= 180.0f * rotationLeft * deltaTime;
	angle += 180.0f * rotationRight * deltaTime;

	velocity += accelerationForward;
	velocity -= accelerationBackward;

	x += cos(Util::deg2rad(angle)) * velocity * deltaTime;
	y += sin(Util::deg2rad(angle)) * velocity * deltaTime;
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
}