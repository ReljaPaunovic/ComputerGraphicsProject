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
	stbi_uc* pixels = stbi_load("textures/minemat.png", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

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

	glMatrixMode(GL_MODELVIEW);
	glScalef(100, 100, 100);

	GLfloat mat_specular[] = {10.0, 10.0, 10.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {this->x, this->y - 200, -50.0, 0.0};
	glTranslatef(this->x, this->y, 2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
	//glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);
	if(model!=NULL)
	model->draw();
	else
		std::cout<<("arg")<<std::endl;


	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);

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
