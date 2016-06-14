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
#include "Framebuffer.h"
#include <vector>
#include <iostream>
#include "Enemy.h"
#include "Boss.h"
#include "Util.h"
#include "OBJModel.h"
#include <random>
#include <cmath>
#include <algorithm>

#include "main.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


const int WIDTH = 800;
const int HEIGHT = 600;

std::vector<GameObject*> gameObjects;
Player* player;
Camera* camera;
Enemy* enemy;
Background* background;
GameObject* boss;

Stopwatch frameTimer;
Stopwatch gameTimer;

// Post-processing related objects
Framebuffer framebuffers[2];
GLuint ppShaders[2];
GLint playerPositionUniformLoc[2];
GLint timeUniformLoc[2];

GLint mountainShader;

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
	if (obj1->collider == nullptr || obj2->collider == nullptr) return;

	if (obj1->collider->type == CIRCLE && obj2->collider->type == CIRCLE) {
		double dist = distanceCalculate(obj1->x + obj1->cx, obj1->y + obj1->cy, obj2->x + obj2->cx, obj2->y + obj2->cy);
		if (dist <= (obj1->collider->r + obj2->collider->r)) {
			obj1->onCollide(obj2);
			obj2->onCollide(obj1);
		}
	} // Colission with not rotated rectangle
	else {
		if ((obj1->collider->type == CIRCLE && obj2->collider->type == RECTANGLE) || (obj1->collider->type == RECTANGLE && obj2->collider->type == CIRCLE)) {
			if (obj2->collider->type == CIRCLE) {
				GameObject * temp = obj1;
				obj1 = obj2;
				obj2 = temp;
			}
			float x = abs((obj1->x) - (obj2->x));
			float y = abs((obj1->y) - (obj2->y));

			if (x > (obj2->collider->width / 2 + obj1->collider->r) || y > (obj2->collider->height / 2 + obj1->collider->r)) {
				return;
			}
			if (x <= (obj2->collider->width / 2) || y <= (obj2->collider->height / 2)) {
				obj1->onCollide(obj2);
				obj2->onCollide(obj1);

			}
		}
	}
}

void checkCollisions() {
	std::vector<GameObject*> gameObjectsCopy = gameObjects;
	int size = gameObjectsCopy.size();
	// If needed, implement better
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {	
			checkCollision(gameObjectsCopy[i], gameObjectsCopy[j]);
		}
	}

}

/*void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userData) {
	std::cerr << "OpenGL: " << message << std::endl;
}*/

GLuint createShaderProgram(const std::string& vertexShaderFile, const std::string& fragShaderFile) {
	std::string vertexShaderSrc = Util::readFile(vertexShaderFile);
	std::string fragShaderSrc = Util::readFile(fragShaderFile);
	const char* vertexShaderSrcPtr = vertexShaderSrc.c_str();
	const char* fragShaderSrcPtr = fragShaderSrc.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrcPtr, nullptr);
	glCompileShader(vertexShader);

	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

	std::cerr << "vertex shader (" << vertexShaderFile << "):" << std::endl;
	std::cerr << buffer << std::endl;

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSrcPtr, nullptr);
	glCompileShader(fragShader);

	glGetShaderInfoLog(fragShader, 512, NULL, buffer);

	std::cerr << "fragment shader (" << fragShaderFile << "):" << std::endl;
	std::cerr << buffer << std::endl;

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	glGetProgramInfoLog(shaderProgram, 512, nullptr, buffer);

	std::cerr << "link log:" << std::endl;
	std::cerr << buffer << std::endl;

	return shaderProgram;
}

void initDisplay() {
//	glEnable(GL_DEBUG_OUTPUT);
//	glDebugMessageCallback(debugCallback, nullptr);
	
	framebuffers[0] = Framebuffer(WIDTH, HEIGHT);
	framebuffers[1] = Framebuffer(WIDTH, HEIGHT);

	// Set up clear values
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// Create shader programs

	setShader(0);

	mountainShader = createShaderProgram("shaders/mountain.vert", "shaders/mountain.frag");
}

int minx=0;
int maxx=0;
const double spawnFactor = 1000;
const double SpawnScaler = 1;
const int spawnRangeMin = -400;
const int spawnRangeMax = 1200;
std::default_random_engine generator;
std::exponential_distribution<double> distribution(SpawnScaler);

void enemySpawner(float deltatime){

	int x = (int)camera->getX();
	if(x > maxx || x < minx ){
		if((maxx-minx)>distribution(generator)/deltatime*spawnFactor){
			enemy = new Enemy();
			enemy->y=(float) ((rand()%(spawnRangeMax-spawnRangeMin))+spawnRangeMin);
			gameObjects.push_back(enemy);

			//if( (int)abs(player->angle - 90) % 180 > 90 ){
			if(abs((int) (player->angle-90))%180>90){
				enemy->x=x-10.0f;

			}else{
				enemy->x=x+WIDTH+10.0f;
			}
		}
	}

	if(maxx<x)
		maxx=x;
	if(minx>x)
		minx=x;
}

void display() {
	float deltaTime = frameTimer.time();
	frameTimer.restart();
	
	// Draw game world to post-processing buffer
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[0].fbo);
	glUseProgram(0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	checkCollisions();
	//enemySpawner(deltaTime);

	drawGameObjects(deltaTime);

	// Render quad with first post-processing pass to second
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffers[1].fbo);
	glUseProgram(ppShaders[0]);

	if (playerPositionUniformLoc[0] != -1) {
		glUniform2f(playerPositionUniformLoc[0], player->getScreenPos(camera).x, player->getScreenPos(camera).y);
	}
	if (timeUniformLoc[0] != -1) {
		glUniform1f(timeUniformLoc[0], gameTimer.time());
	}

	drawPostProcessing(deltaTime, 0);

	// Render scene with second post-processing pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(ppShaders[1]);

	if (playerPositionUniformLoc[1] != -1) {
		glUniform2f(playerPositionUniformLoc[1], player->getScreenPos(camera).x, player->getScreenPos(camera).y);
	}
	if (timeUniformLoc[1] != -1) {
		glUniform1f(timeUniformLoc[1], gameTimer.time());
	}

	drawPostProcessing(deltaTime, 1);

	// Draw UI
	glUseProgram(0);
	drawUI(deltaTime);

	glutSwapBuffers();

	glutPostRedisplay();
}

void drawPostProcessing(float deltaTime, int pass) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	// Reset projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, framebuffers[pass].colorTexture);
	glBegin(GL_QUADS);
		glColor3f(1, 1, 1);

		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);

		glTexCoord2f(1, 1);
		glVertex2f(1, 1);
		
		glTexCoord2f(1, 0);
		glVertex2f(1, -1);

		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawGameObjects(float deltaTime) {
	// Set up world projection
	camera->updatePosition(player);
	camera->setProjection();

	// Draw background
	glUseProgram(mountainShader);
	glUniform1f(glGetUniformLocation(mountainShader, "cameraX"), camera->getX());
	background->render(camera->getX());
	glUseProgram(0);

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
		glVertex2f(std::max(player->getHealth(),0.0f), 0);
		glVertex2f(std::max(player->getHealth(),0.0f), 1);
		glVertex2f(0, 1);
	glEnd();
}

void setShader(int i) {
	if (i == 0) {
		ppShaders[0] = createShaderProgram("shaders/postprocessing.vert", "shaders/postprocessing.frag");
		ppShaders[1] = createShaderProgram("shaders/postprocessing2.vert", "shaders/postprocessing2.frag");
	} else if (i == 1) {
		ppShaders[0] = createShaderProgram("shaders/postprocessing.vert", "shaders/oilpainting.frag");
		ppShaders[1] = createShaderProgram("shaders/postprocessing2.vert", "shaders/postprocessing2.frag");
	} else if (i == 2) {
		ppShaders[0] = createShaderProgram("shaders/postprocessing.vert", "shaders/headvission.frag");
		ppShaders[1] = createShaderProgram("shaders/postprocessing2.vert", "shaders/postprocessing2.frag");
	} else {
		ppShaders[0] = createShaderProgram("shaders/postprocessing.vert", "shaders/HandDrawn.frag");
		ppShaders[1] = createShaderProgram("shaders/postprocessing2.vert", "shaders/postprocessing2.frag");

	}

	for (int i = 0; i < 2; i++) {
		playerPositionUniformLoc[i] = glGetUniformLocation(ppShaders[i], "playerPosition");
		timeUniformLoc[i] = glGetUniformLocation(ppShaders[i], "time");
	}
}

//take keyboard input into account
void keyboardDown(unsigned char key, int x, int y) {
	player->handleKeyboard(key, true);
}

void keyboardUp(unsigned char key, int x, int y) {
	player->handleKeyboard(key, false);

	switch (key) {
	case '1':
	case '2':
	case '3':
	case '4':
		setShader(key - '1');
		break;

	case 27:
		exit(0);
	}
}

int main(int argc, char** argv) {
	// TODO: Only apply oil painting to terrain
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

	boss = new Boss();
	gameObjects.push_back(boss);
	background = new Background();
	gameObjects.push_back(player);

	// Set up rendering
	glewInit();
	initDisplay();
	gameObjects.push_back(enemy);

	// Start game
	glutMainLoop();
}
