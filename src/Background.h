#pragma once
#include "GameObject.h"
#include "OBJModel.h"
class Background 	
{
public:
	Background():
		plane("models/mountains.obj"){

		int textureWidth, textureHeight;
		int textureComponents;
		stbi_uc* pixels = stbi_load("textures/rock.jpg", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

		glGenTextures(1, &textureRock);
		glBindTexture(GL_TEXTURE_2D, textureRock);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(pixels);

		pixels = stbi_load("textures/snow.jpg", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

		glGenTextures(1, &textureSnow);
		glBindTexture(GL_TEXTURE_2D, textureSnow);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(pixels);

		pixels = stbi_load("textures/sky.jpg", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

		glGenTextures(1, &textureSky);
		glBindTexture(GL_TEXTURE_2D, textureSky);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(pixels);

		pixels = stbi_load("textures/rock_grass.jpg", &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

		glGenTextures(1, &textureRockGrass);
		glBindTexture(GL_TEXTURE_2D, textureRockGrass);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(pixels);
	}

	~Background();


	void layer1(int ,float );
	void render(float);
private:
		OBJModel plane;

		GLuint textureSky;
		GLuint textureRock;
		GLuint textureSnow;
		GLuint textureRockGrass;
};

