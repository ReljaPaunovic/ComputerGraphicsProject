#include "Enemy.h"
#include <stdio.h>
#include <GL/GL.h>
#define PI 3.14
#include <cmath>

Enemy::Enemy()
{
	x = 400;
	y = 150;
	cx = 48;
	cy = 48;
	angle = 0;
	collider = new Collider(90);
}


Enemy::~Enemy()
{
}

void Enemy::render() {

	setupTransformation();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex2f(0, 0);
		glVertex2f(96, 0);
		glVertex2f(96, 96);
		glVertex2f(0, 96);
	glEnd();

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

void Enemy::tick(float deltaTime) {

}

void Enemy::onCollide(GameObject* other) {
	printf("Enemy ---> Player\n");

}