#include "Background.h"
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <time.h>

void Background::render(float viewx){
	static time_t start = time(nullptr);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(viewx + 400, 300, -250);
	glScalef(400, -1000, 500);
	GLfloat mat_specular[] = {100.0, 100.0, 100.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	GLfloat light_position[] = {0, 0 - 0, -50.0, 0.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureRock);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureSnow);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureRockGrass);

	plane.draw();

	glUseProgram(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureSky);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1000, 1000);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, -900);

		glTexCoord2f(1, 0);
		glVertex3f(800, 0, -900);

		glTexCoord2f(1, 1);
		glVertex3f(800, 600, -900);

		glTexCoord2f(0, 1);
		glVertex3f(0, 600, -900);
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

Background::~Background()
{
}






