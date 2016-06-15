#include "BossSegment.h"
#include <GL/glut.h>
#include "main.h"
#include "OBJModel.h"
#include "Util.h"
#include "Projectile.h"
#include "AnimateObject.h"
//#include "Boss.h"

static GLint shader = -1;
static GLint texture = -1;

BossSegment::BossSegment(BossSegment* obj, float x, float y, int i)
{
	collider = new Collider(20);
	size = 40;

	//Hard coded value, should be the same as Boss->numSegments ,  make sure it is
	int totalNumberOfSegments = 16;

	this->x = x + 2*size * (i+1);
	this->y = y;

	//printf("(x,y,i) = (%f, %f, %d) \n", this->x, this->y, i);
	segmentNum = i;
	previousSegment = obj;

	if (texture == -1) {
		texture = Util::loadTexture("textures/scales.jpg");
	}
	
	if (shader == -1) {
		shader = Util::createShaderProgram("shaders/mesh.vert", "shaders/mesh.frag");
	}
	
	if (obj != nullptr) {
		speed = obj->speed;
		obj->nextSegment = this;
	}
	else {
		//SPEED IS HARDCODED TO BOSS
		speed = 2;
	}
	if (i == totalNumberOfSegments - 1)
		nextSegment = nullptr;
}

BossSegment::~BossSegment()
{
}

void BossSegment::tick(float deltaTime)
{
	if (previousSegment != nullptr) {
		xDirection = previousSegment->x - this->x;
		yDirection = previousSegment->y - this->y;
		float length = sqrt(xDirection*xDirection + yDirection*yDirection);
		if (length != 0) {
			xDirection /= length;
			yDirection /= length;
		}
		if (length >= size*2) {
			this->x += xDirection * speed;
			this->y += yDirection * speed;
		}
	}
	else {
		xDirection = boss->x - this->x;
		yDirection = boss->y - this->y;
		float length = sqrt(xDirection*xDirection + yDirection*yDirection);
		if (length != 0) {
			xDirection /= length;
			yDirection /= length;
		}
		if (length >= size*2) {
			this->x += xDirection * speed;
			this->y += yDirection * speed;
		}
	}
	
	//printf("(x,y,i) = (%f, %f, %d) \n", this->x, this->y, segmentNum);
}

void BossSegment::render()
{
	setupTransformation();
	glMatrixMode(GL_MODELVIEW);

	//glColor3f(0.0f, 1.0f, 0.0f);
	
	glScalef(size/2, size/2, size/2);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	GLint originalProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &originalProgram);
	glUseProgram(shader);

	glUniform1i(glGetUniformLocation(shader, "enableSimplification"), GL_FALSE);
	//glUniform1f(glGetUniformLocation(shader, "simplifyGridSpacing"), Util::lerp(0.1f, 10.0f, 1.0f - health / 100.0f));
	
	static OBJModel lol("models/snake_segment.obj");
	lol.draw();

	glDisable(GL_TEXTURE_2D);
	
	glUseProgram(originalProgram);

	resetTransformation();
}


void BossSegment::onCollide(GameObject * other)
{
	if (dynamic_cast<Player*>(other) != NULL) {
		//if PLayer
	}
	if (dynamic_cast<Projectile*>(other) != NULL) {
		//if projectile
		if(nextSegment != nullptr)
			this->nextSegment->onCollide(other);
		this->animateDeath();
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
	}
}

void BossSegment::animateDeath()
{
	AnimateObject * anObj = new AnimateObject(this->x, this->y, 0);
	gameObjects.push_back(anObj);
}
