#include "Enemy.h"
#include <GL/GL.h>


Enemy::Enemy()
{
	x = 400;
	y = 150;
	cx = 48;
	cy = 48;
	angle = 0;
	collider = new Collider(5);
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
	resetTransformation();

}

void Enemy::tick(float deltaTime) {

}

void Enemy::onCollide(GameObject* other) {


}