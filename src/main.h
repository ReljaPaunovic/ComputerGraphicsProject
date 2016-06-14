#pragma once

#include <vector>
#include "GameObject.h"
#include "Player.h"

void drawGameObjects(float deltaTime);
void drawUI(float deltaTime);
void drawPostProcessing(float deltaTime, int pass);
void setShader(int i);

extern std::vector<GameObject*> gameObjects;
extern GameObject* boss;
extern Player* player;
