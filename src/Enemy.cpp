#include "Enemy.h"
#include <stdio.h>
#include <GL/freeglut.h>
#include "Player.h"
#include <cmath>
#include <typeinfo>
#include "main.h"
#include <algorithm>
#include <random>
#include "Projectile.h"
#include "OBJModel.h"
#include "Util.h"

static GLint shader = -1;
static GLint texture = -1;

Enemy::Enemy()
{

	x = 400;
	y = 150;
	cx = 0;
	cy = 0;
	angle = 0;
	collider = new Collider(65);
	
	// this is to lower the chance bombs will overlap
	z = (float) (10 + rand() % 100);

	if (texture == -1) {
		texture = Util::loadTexture("textures/minemat.png");
	}

	if (shader == -1) {
		shader = Util::createShaderProgram("shaders/mesh.vert", "shaders/mesh.frag");
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis;
	spinRate = dis(gen);
}


Enemy::~Enemy()
{
}

void Enemy::render() {

	setupTransformation();

	glMatrixMode(GL_MODELVIEW);
	glRotatef(spin, 1, 1, 1);

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
	spin += deltaTime * spinRate * 45.0f;
}


void Enemy::onCollide(GameObject* other) {
	//printf("Enemy ---> Player\n");
	//Check if it is a PLAYER
	if (dynamic_cast<Player*>(other) != NULL) {
		((Player*)other)->setHealth(((Player*)other)->getHealth() - this->getHealth());
		this->animateDeath();
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
		((Player*)other)->killCount++;
	}
	//Check if it is other enemy
	if (dynamic_cast<Enemy*>(other) != NULL) {
		//this->animateDeath();
		//gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());

	}
	if (dynamic_cast<Projectile*>(other) != NULL) {
		this->animateDeath();
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
		player->killCount++;
	}
}
