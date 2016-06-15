#include "Background.h"
#include <GL/glew.h>
#include "main.h"

void Background::render(float viewx){
	renderMountains(viewx);
	renderSky();
}

void Background::renderMountains(float viewx) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(viewx + WIDTH / 2, 300, -300);
	glScalef(WIDTH / 2, -1000, 500);
	
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureRock);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureSnow);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureRockGrass);

	plane.draw();
}

void Background::renderSky() {
	glUseProgram(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureSky);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, -1000, 1000);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -900);

	glTexCoord2f(1, 0);
	glVertex3f(WIDTH, 0, -900);

	glTexCoord2f(1, 1);
	glVertex3f(WIDTH, HEIGHT, -900);

	glTexCoord2f(0, 1);
	glVertex3f(0, HEIGHT, -900);
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

Background::~Background()
{
}






