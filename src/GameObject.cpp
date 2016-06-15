#include "GameObject.h"
#include "Camera.h"
#include "AnimateObject.h"
#include "main.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::setupTransformation() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
		glTranslatef((float) x, (float) y, 0.0f);
		glRotatef((float) angle, 0.0f, 0.0f, 1.0f);
		glTranslatef((float) -cx, (float) -cy, 0.0f);
}

void GameObject::resetTransformation() {
	glPopMatrix();
}

glm::vec2 GameObject::getScreenPos(Camera* camera) {
	glm::vec4 pos(cy, cy, 0.0f, 1.0f);

	glm::mat4 transform;

	transform = glm::translate(transform, glm::vec3(-camera->getX(), -camera->getY(), 0.0f));

	transform = glm::translate(transform, glm::vec3(x, y, 0));
	transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::translate(transform, glm::vec3(-cx, -cy, 0.0f));

	return glm::vec2(transform * pos);
}

void GameObject::animateDeath() {
	AnimateObject* anObj = new AnimateObject(this->x, this->y, 0);
	gameObjects.push_back(anObj);
}