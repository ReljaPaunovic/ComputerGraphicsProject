/*
* RedSquare.c
*
*   This program draws a red rectangle on a blue background.
*
*/

#include <GL/glut.h>
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include <vector>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const int WIDTH = 800;
const int HEIGHT = 600;

std::vector<GameObject*> gameObjects;
Player* player;
Camera* camera;
Background* background;

std::chrono::steady_clock::time_point lastFrame;

void drawGameObjects(float deltaTime);
void drawUI(float deltaTime);

void display() {
	auto timeNow = std::chrono::high_resolution_clock::now();
	float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(timeNow - lastFrame).count() / 1e6f;
	lastFrame = timeNow;

	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawGameObjects(deltaTime);
	drawUI(deltaTime);
	
	glFlush();

	glutPostRedisplay();
}

void drawGameObjects(float deltaTime) {
	// Set up world projection
	camera->updatePosition(player);
	camera->setProjection();

	// Draw background
	background->render(camera->getX());

	for (GameObject* obj : gameObjects) {
		obj->tick(deltaTime);
		obj->render();
	}
}

void drawUI(float deltaTime) {
	// Draw over everything
	glClear(GL_DEPTH_BUFFER_BIT);

	// Set up projection to map directly to pixel coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(30, 30, 0);
	glScalef(2, 30, 0);

	// Draw player health bar
	glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0, 0);
		glVertex2f(100, 0);
		glVertex2f(100, 1);
		glVertex2f(0, 1);
		glVertex2f(0, 0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(player->getHealth(), 0);
		glVertex2f(player->getHealth(), 1);
		glVertex2f(0, 1);
	glEnd();
}

//take keyboard input into account
void keyboardDown(unsigned char key, int x, int y) {
	player->handleKeyboard(key, true);
}

void keyboardUp(unsigned char key, int x, int y) {
	player->handleKeyboard(key, false);

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
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	putenv( (char *) "__GL_SYNC_TO_VBLANK=1" );

	// Initialize game world
	player = new Player();
	camera = new Camera(WIDTH, HEIGHT);
	background = new Background();
	gameObjects.push_back(player);
	
	lastFrame = std::chrono::high_resolution_clock::now();

	// Start game
	glutMainLoop();
}
