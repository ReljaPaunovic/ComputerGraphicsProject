#include "Boss.h"
#include <iostream>

Boss::~Boss()
{
}

void Boss::loadTextures() {
	eyeTexture = loadTexture("textures/hal.png");
	rivetTexture = loadTexture("textures/metal_rivets.jpg");
}

void Boss::tick(float deltaTime) {

}

void Boss::render() {
	setupTransformation();

	glMatrixMode(GL_MODELVIEW);
	glScalef(30, 30, 30);

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

	modelHead.draw();

	glBindTexture(GL_TEXTURE_2D, eyeTexture);

	glTranslatef(0, 0, 2);

	modelEye.draw();

	glTranslatef(-1.5, 0, 0);

	modelEye.draw();

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
}

void Boss::onCollide(GameObject* other) {

}

GLuint Boss::loadTexture(const std::string& filename) {
	GLuint tex;

	int textureWidth, textureHeight;
	int textureComponents;
	stbi_uc* pixels = stbi_load(filename.c_str(), &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(pixels);

	return tex;
}