/*
* RedSquare.c
*
*   This program draws a red rectangle on a blue background.
*
*/

#define GLEW_STATIC
#include <GL/glew.h>

#include <GL/glut.h>
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include "Stopwatch.h"
#include <vector>
#include <iostream>
#include "Enemy.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const int WIDTH = 800;
const int HEIGHT = 600;

std::vector<GameObject*> gameObjects;
Player* player;
Camera* camera;
Enemy* enemy;
Background* background;

Stopwatch frameTimer;

// Post-processing related objects
GLuint framebuffer;
GLuint texColorBuffer;

void drawGameObjects(float deltaTime);
void drawUI(float deltaTime);
void drawPostProcessing(float deltaTime);

double distanceCalculate(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}

void checkCollision(GameObject* obj1, GameObject* obj2) {
	if (obj1->collider->type == CIRCLE && obj2->collider->type == CIRCLE) {
		double dist = distanceCalculate(obj1->x + obj1->cx, obj1->y + obj1->cy, obj2->x + obj2->cx, obj2->y + obj2->cy);
		if (dist <= (obj1->collider->r + obj2->collider->r)) {
			obj1->onCollide(obj2);
			obj2->onCollide(obj1);
		}
	}
	else if ((obj1->collider->type == CIRCLE && obj2->collider->type == RECTANGLE) || (obj1->collider->type == RECTANGLE && obj2->collider->type == CIRCLE)) {



	}
}

void checkCollisions() {
	int size = gameObjects.size();
	// If needed, implement better
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {	
			checkCollision(gameObjects[i], gameObjects[j]);
		}
	}

}

void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userData) {
	std::cerr << "OpenGL: " << message << std::endl;
}

void initDisplay() {
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(debugCallback, nullptr);
	
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Create texture to hold color buffer
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Create renderbuffer for depth buffer
	GLuint rboDepthStencil;
	glGenRenderbuffers(1, &rboDepthStencil);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Set up clear values
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display() {
	float deltaTime = frameTimer.time();
	frameTimer.restart();
	
	// Render graphics to post-processing buffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	checkCollisions();
	
	drawGameObjects(deltaTime);
	drawUI(deltaTime);

	// Render scene with post-processing shader
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	drawPostProcessing(deltaTime);

	glutSwapBuffers();

	glutPostRedisplay();
}

void drawPostProcessing(float deltaTime) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	// Reset projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);

		glTexCoord2f(0, 1);
		glVertex2i(-1, 1);

		glTexCoord2f(1, 1);
		glVertex2i(1, 1);
		
		glTexCoord2f(1, 0);
		glVertex2i(1, -1);

		glTexCoord2f(0, 0);
		glVertex2i(-1, -1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawGameObjects(float deltaTime) {
	// Set up world projection
	camera->updatePosition(player);
	camera->setProjection();

	// Draw background
	background->render(camera->getX());

	// Copy is made such that game objects can remove themselves or spawn new game objects
	std::vector<GameObject*> gameObjectsCopy = gameObjects;

	for (GameObject* obj : gameObjectsCopy) {
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
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// Initialize game world
	player = new Player();
	camera = new Camera(WIDTH, HEIGHT);
	background = new Background();
	enemy = new Enemy();
	gameObjects.push_back(enemy);
	gameObjects.push_back(player);

	// Set up rendering
	glewInit();
	initDisplay();

	// Start game
	glutMainLoop();
}
