/*
* RedSquare.c
*
*   This program draws a red rectangle on a blue background.
*
*/

#include <GL/glut.h>
#include "GameObject.h"
#include "Player.h"
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

std::vector<GameObject*> gameObjects;
Player* player;

int cameraX = 0, cameraY = 0;

void display() {
	/* clear window */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Setup projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(cameraX, cameraX + WIDTH, cameraY + HEIGHT, cameraY);

	// TODO: Limit framerate
	for (GameObject* obj : gameObjects) {
		obj->tick();
		obj->render();
	}

	glFlush();

	glutPostRedisplay();
}

//take keyboard input into account
void keyboard(unsigned char key, int x, int y)
{
	player->handleKeyboard(key);

	switch (key) {
	case 27:
		exit(0);
	}
}

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - WIDTH / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2 - HEIGHT / 2);
	glutCreateWindow("Lightbringer");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	// Initialize game world
	player = new Player();
	gameObjects.push_back(player);

	// Start game
	glutMainLoop();
}