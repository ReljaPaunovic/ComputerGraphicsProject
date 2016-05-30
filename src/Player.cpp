#include "Player.h"
#include <GL/freeglut.h>


Player::Player()
{
	x = 100;
	y = 100;
}


Player::~Player()
{
}

void Player::handleKeyboard(unsigned char key) {
	if (key == 'w') {
		y--;
	} else if (key == 's') {
		y++;
	} else if (key == 'd') {
		x++;
	} else if (key == 'a') {
		x--;
	}
}

void Player::tick() {
	// TODO
}

void Player::render() {
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, y);
		glVertex2f(x + 10, y);
		glVertex2f(x + 10, y + 10);
		glVertex2f(x, y + 10);
	glEnd();
}