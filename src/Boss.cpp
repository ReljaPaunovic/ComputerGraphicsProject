#include "Boss.h"
#include <GL/glut.h>
#include <iostream>
#include "main.h"
#include <cmath>
#include "BossSegment.h"
#include "Util.h"
#include "Projectile.h"



Boss::~Boss()
{
}

void Boss::loadTextures() {
	x = 32000;
	y = 750;
	speed = 100;
	eyeTexture = Util::loadTexture("textures/headscales.png");
	rivetTexture = Util::loadTexture("textures/headscales.jpg");
}


void Boss::tick(float deltaTime) {

	//if (firstTime) {
		xDirection = player->x - x;
		yDirection = player->y - y;

		float normalizationFactor = sqrt(xDirection*xDirection + yDirection*yDirection);
		xDirection /= normalizationFactor;
		yDirection /= normalizationFactor;

		x += xDirection * speed * deltaTime;
		y += yDirection * speed * deltaTime;
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

void Boss::render(bool shadow) {
	setupTransformation();

	glMatrixMode(GL_MODELVIEW);

	float dir=(atan2(xDirection,yDirection)/(3.14*2))*-360+90;
	std::cout<<dir<< " ";
	glRotatef(dir,0,0,1);
	glScalef(15, 15, 15);

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
	//***********
	GLint originalProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &originalProgram);
	glUseProgram(shader);

	glUniform1i(glGetUniformLocation(shader, "enableSimplification"), GL_TRUE);
	glUniform1f(glGetUniformLocation(shader, "simplifyGridSpacing"), Util::lerp(0.1f / 30, 10.0f / 30, (1 - currentNumSegments * 1.0f / numSegments)));
	//printf("%f \n", 1 - currentNumSegments * 1.0f / numSegments);

	modelHead.draw();

	glUseProgram(originalProgram);

	

/*	glBindTexture(GL_TEXTURE_2D, eyeTexture);

	glTranslatef(0, 0, 2);

	modelEye.draw();

	glTranslatef(-1.5, 0, 0);

	modelEye.draw();
*/
	glDisable(GL_TEXTURE_2D);
	

	glDisable(GL_LIGHTING);

	resetTransformation();
}

void Boss::onCollide(GameObject* other) {

	if (dynamic_cast<Player*>(other) != NULL) {
		// If the tail has been destroyed
		if (tail == nullptr) {
			((Player*)other)->animateDeath();
			this->animateDeath();
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), other), gameObjects.end());
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
		}
		//If not, kill the player
		else {
			((Player*)other)->setHealth(0);
			((Player*)other)->animateDeath();
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), other), gameObjects.end());
		}
	}
	if (dynamic_cast<Projectile*>(other) != NULL) {
		if (tail == nullptr) {
			// kill boss and erase projectile from the game
			this->animateDeath();
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), other), gameObjects.end());
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
		}
		else {
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), other), gameObjects.end());
		}
	}
}
