#pragma once
#include "GameObject.h"
#include "OBJModel.h"
#include "Util.h"
class Background 	
{
public:
	Background():
		plane("models/plane.obj"){

		textureRock = Util::loadTexture("textures/rock.jpg");
		textureSnow = Util::loadTexture("textures/snow.jpg");
		textureSky = Util::loadTexture("textures/sky.jpg");
		textureRockGrass = Util::loadTexture("textures/rock_grass.jpg");
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

