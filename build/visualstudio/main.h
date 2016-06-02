#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include "GameObject.h"
#include "Player.h"
#include "Camera.h"
#include "Background.h"
#include "Stopwatch.h"
#include <vector>
#include "Enemy.h"
#include <random>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "main.h"

std::vector<GameObject*> gameObjects;