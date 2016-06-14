#include "Enemy.h"
#include <stdio.h>
#include <GL/freeglut.h>
#include "Player.h"
#define PI 3.14
#include <cmath>
#include <typeinfo>
#include "main.h"
#include <algorithm>
#include "AnimateObject.h"
#include "Projectile.h"


Enemy::Enemy()
{
	x = 400;
	y = 150;
	cx = 48;
	cy = 48;
	angle = 0;
	collider = new Collider(90);
	
	// this is to lower the chance bombs will overlap
	z = (float) (10 + rand() % 100);
	

	int textureWidth, textureHeight;
	int textureComponents;
	stbi_uc* pixels = stbi_load("textures/mine.png", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

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


Enemy::~Enemy()
{
}

void Enemy::render() {

	setupTransformation();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, z);

		glTexCoord2f(1, 0);
		glVertex3f(96, 0, z);

		glTexCoord2f(1, 1);
		glVertex3f(96, 96, z);

		glTexCoord2f(0, 1);
		glVertex3f(0, 96, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	resetTransformation();

}

void Enemy::tick(float deltaTime) {

}


void Enemy::onCollide(GameObject* other) {
	//printf("Enemy ---> Player\n");
	//Check if it is a PLAYER
	if (dynamic_cast<Player*>(other) != NULL) {
		((Player*)other)->setHealth(((Player*)other)->getHealth() - this->getHealth());
		this->animateDeath();
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
	}
	//Check if it is other enemy
	if (dynamic_cast<Enemy*>(other) != NULL) {
		//this->animateDeath();
		//gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());

	}
	if (dynamic_cast<Projectile*>(other) != NULL) {
		this->animateDeath();
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
	}
}

void Enemy::animateDeath(){
	AnimateObject * anObj = new AnimateObject(this->x, this->y, this->z);
	gameObjects.push_back(anObj);
}