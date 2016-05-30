#pragma once
#include "GameObject.h"
class Player:
	public GameObject
{
public:
	Player();
	~Player();

	void handleKeyboard(unsigned char key);

	void tick();
	void render();
};

