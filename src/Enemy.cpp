#include "Enemy.h"
#include <stdio.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Player.h"
#define PI 3.14
#include <cmath>
#include <typeinfo>
#include "main.h"
#include <algorithm>
#include "AnimateObject.h"
#include "Projectile.h"
#include "OBJModel.h"
#include "Util.h"

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

	texture = Util::loadTexture("textures/minemat.png");

	shader = Util::createShaderProgram("shaders/mesh.vert", "shaders/mesh.frag");
}


Enemy::~Enemy()
{
}

void Enemy::render() {

	setupTransformation();

	GLint originalProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &originalProgram);
	glUseProgram(shader);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	static OBJModel* mine = new OBJModel("models/mine.obj");
	mine->draw();

	glDisable(GL_TEXTURE_2D);

	glUseProgram(originalProgram);
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
