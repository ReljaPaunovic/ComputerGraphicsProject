#include "BossSegment.h"
#include <GL/glut.h>
#include "main.h"



BossSegment::BossSegment(BossSegment* obj, float x, float y, int i)
{
	collider = nullptr;
	size = 40;

	this->x = x + 2*size * (i+1);
	this->y = y;

	//printf("(x,y,i) = (%f, %f, %d) \n", this->x, this->y, i);
	segmentNum = i;
	previousSegment = obj;
}

BossSegment::~BossSegment()
{
}

void BossSegment::tick(float deltaTime)
{
	//this->x = boss->x;
	//this->y = boss->y;
	if (previousSegment != nullptr) {
		xDirection = previousSegment->x - this->x;
		yDirection = previousSegment->y - this->y;
		float length = sqrt(xDirection*xDirection + yDirection*yDirection);
		if (length != 0) {
			xDirection /= length;
			yDirection /= length;
		}
		if (length >= size*2) {
			this->x += xDirection;
			this->y += yDirection;
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
			this->x += xDirection;
			this->y += yDirection;
		}
	}
	
	//printf("(x,y,i) = (%f, %f, %d) \n", this->x, this->y, segmentNum);
}

void BossSegment::render()
{
	setupTransformation();
	glMatrixMode(GL_MODELVIEW);
	glColor3f(0.0f, 1.0f, 0.0f);
	//glRotatef(30, 0, 0, 1);
	//glTranslatef(2 * 2, 0, 0);
	
	glScalef(size/2, size/2, size/2);
	//glTranslatef(2 * 2 * segmentNum, 0, 0);
	glutSolidSphere(2.0f, 50, 50);

	resetTransformation();
}


void BossSegment::onCollide(GameObject * other)
{
}