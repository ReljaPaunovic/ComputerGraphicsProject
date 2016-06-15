#include "Boss.h"
#include <GL/glut.h>
#include <iostream>
#include "main.h"
#include <cmath>
#include "BossSegment.h"
#include "Util.h"

Boss::~Boss()
{
}

void Boss::loadTextures() {
	x = 1000;
	y = 100;
	speed = 2;
	eyeTexture = Util::loadTexture("textures/hal.png");
	rivetTexture = Util::loadTexture("textures/metal_rivets.jpg");
}


void Boss::tick(float deltaTime) {

	//if (firstTime) {
		xDirection = player->x - x;
		yDirection = player->y - y;

		float normalizationFactor = sqrt(xDirection*xDirection + yDirection*yDirection);
		xDirection /= normalizationFactor;
		yDirection /= normalizationFactor;

		x += xDirection * speed;
		y += yDirection * speed;
	//}
	/*else {
		float x1 = player->x;
		float x2 = previousX;

		float y1 = player->y;
		float y2 = previousY;


		float dot = x1*x2 + y1*y2;
		float det = x1*y2 - y1*x2;
		angle = atan2(det, dot);

		x += cos(Util::deg2rad(angle)) * velocity * deltaTime;
		y += sin(Util::deg2rad(angle)) * velocity * deltaTime;

		firstTime = false;
		previousX = player->x;
		previousY = player->y;
	}*/
}

void Boss::render() {
	setupTransformation();

	glMatrixMode(GL_MODELVIEW);
	glScalef(30, 30, 30);

	GLfloat mat_specular[] = {10.0, 10.0, 10.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {this->x, this->y - 200, -50.0, 0.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, rivetTexture);

	modelHead.draw();

	glBindTexture(GL_TEXTURE_2D, eyeTexture);

	glTranslatef(0, 0, 2);

	modelEye.draw();

	glTranslatef(-1.5, 0, 0);

	modelEye.draw();

	glDisable(GL_TEXTURE_2D);
	

	glDisable(GL_LIGHTING);

	resetTransformation();
}

void Boss::onCollide(GameObject* other) {

}
