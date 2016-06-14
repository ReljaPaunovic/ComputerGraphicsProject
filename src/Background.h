#pragma once
#include "GameObject.h"
#include "OBJModel.h"
class Background 	
{
public:
	Background():
		plane("models/head.obj"){
		}

	~Background();


	void layer1(int ,float );
	void render(float);
private:
		OBJModel plane;
};

