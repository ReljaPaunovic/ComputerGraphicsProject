#pragma once

#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

const bool ENABLE_DEPTH_DEBUG = false;

void drawGameObjects(float deltaTime, bool shadowRender);
void drawUI(float deltaTime);
void drawPostProcessing(float deltaTime, int pass);
void setShader(int i);

extern std::vector<GameObject*> gameObjects;
extern GameObject* boss;
extern Player* player;
extern Camera* camera;

extern float explosionRange;
extern glm::vec2 explosionPos;

extern float shockwaveRange;
extern float shockwaveDistance;

extern bool gameOver;