#include "Projectile.h"
#include "Util.h"
#include <stb_image.h>
#include <cmath>
#define PI 3.14

Projectile::Projectile(float x, float y, float direction, float velocity)
{
	this->x = x;
	this->y = y;
	this->angle = direction;
	this->velocity = velocity;
	collider = new Collider(5);

	cx = 5;
	cy = 5;

	// Load and create texture
	int textureWidth, textureHeight;
	int textureComponents;
	stbi_uc* pixels = stbi_load("textures/bullet.png", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

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


Projectile::~Projectile()
{
}

void Projectile::tick(float deltaTime) {
	x += velocity * cos(Util::deg2rad(angle)) * deltaTime;
	y += velocity * sin(Util::deg2rad(angle)) * deltaTime;
}

void Projectile::onCollide(GameObject* other) {
	// TODO
}

void Projectile::render() {
	setupTransformation();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);

	glTexCoord2f(1, 0);
	glVertex2f(10, 0);

	glTexCoord2f(1, 1);
	glVertex2f(10, 10);

	glTexCoord2f(0, 1);
	glVertex2f(0, 10);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	/*
	glPushMatrix();
	glTranslatef((float)cx, (float)cy, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 300; i++) {
		double angletemp = 2 * PI * i / 300;
		double xtemp = cos(angletemp);
		double ytemp = sin(angletemp);
		glVertex2d(90 * xtemp, 90 * ytemp);
	}
	glPopMatrix();
	*/
	resetTransformation();
}