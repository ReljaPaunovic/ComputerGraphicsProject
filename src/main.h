#pragma once

#include <vector>
#include "GameObject.h"
#include "Player.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

void drawGameObjects(float deltaTime);
void drawUI(float deltaTime);
void drawPostProcessing(float deltaTime, int pass);
void setShader(int i);

extern std::vector<GameObject*> gameObjects;
extern GameObject* boss;
extern Player* player;

extern float explosionRange;
extern glm::vec2 explosionPos;

extern float shockwaveRange;
extern float shockwaveDistance;

extern bool gameOver;