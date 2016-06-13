#include "Boss.h"
#include <iostream>

Boss::~Boss()
{
}

void Boss::tick(float deltaTime) {

}

void Boss::render() {
	setupTransformation();

	glMatrixMode(GL_MODELVIEW);
	glScalef(30, 30, 30);

	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	modelBody.draw();

	glDisable(GL_LIGHTING);
}

void Boss::onCollide(GameObject* other) {

}