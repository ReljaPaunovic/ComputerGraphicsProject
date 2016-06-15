#include "Player.h"
#include "Util.h"
#include "Projectile.h"
#include <cmath>
#include <vector>
#include <stb_image.h>
#include "main.h"
#include <algorithm>
#include "OBJModel.h"
#include "Boss.h"

bool bossSpawned = false;

Player::Player()
{
	x = 100;
	y = 400;
	cx = 15;
	cy = 15;
	collider = new Collider(35);
	velocity = 800;
	//velocity = 0;

	texture = Util::loadTexture("textures/metal_plate.jpg");

	shader = Util::createShaderProgram("shaders/mesh.vert", "shaders/mesh.frag");

	shootSoundBuffer.loadFromFile("sounds/laser_shot.wav");
	shootSound.setBuffer(shootSoundBuffer);
	shootSound.setVolume(50);
}


Player::~Player()
{
}

float Player::getHealth() const {
	return health;
}



void Player::handleKeyboard(unsigned char key, bool down) {
	// Do we need w and s?
	if (key == 'a') {
		rotationLeft = down ? 1.0f : 0.0f;
	} else if (key == 'd') {
		rotationRight = down ? 1.0f : 0.0f;
	} else if (key == 'w') {
		accelerationForward = down ? 1.0f : 0.0f;
	} else if (key == 's') {
		accelerationBackward = down ? 1.0f : 0.0f;
	} else if (key == ' ') {
		firing = down;
	} else if (key == 'j') {
		health -= 1;
	}
}

void Player::tick(float deltaTime) {
	// Force player back down if he goes too far up
	float actualLeft = rotationLeft;
	float actualRight = rotationRight;

	if (-y > upperBoundary) {
		if (angle <= 270 && angle >= 90) {
			//angle += (1 + y / upperBoundary);
			actualLeft = 1;
			actualRight = 0;
		}
		else {
			actualRight = 1;
			actualLeft = 0;
		}
	}

	// Roll player to currently intended roll (based on turning or not)
	float deltaRoll = rollTarget - roll;
	roll += deltaRoll * deltaTime * velocity / 100.0f;

	rollTarget = 0.0f;
	if (rotationLeft) rollTarget += -15;
	if (rotationRight) rollTarget += 15;

	if (health <= 0) {
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
	}
	angle -= 180.0f * actualLeft * deltaTime;
	angle += 180.0f * actualRight * deltaTime;
	// To keep it in range (0, 359)
	if (angle < 0)
		angle += 360;
	if (angle >= 360)
		angle -= 360;

	velocity += accelerationForward;
	velocity -= accelerationBackward;

	x += cos(Util::deg2rad(angle)) * velocity * deltaTime;
	y += sin(Util::deg2rad(angle)) * velocity * deltaTime;
	//printf("angle = %g\n",angle);

	// Destroy if lower than lowerBoundary
	if (-y < lowerBoundary) {
		player->health = 0;
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), this), gameObjects.end());
		animateDeath();
	}

	// Should fire from two guns, but can't be bothered to set up the matrix for that right now
	timeUntilNextFire -= deltaTime;
	if (firing && timeUntilNextFire <= 0.0f) {
		timeUntilNextFire = firingDelay;
		float spawnX = x + cos(Util::deg2rad(angle)) * 25;
		float spawnY = y + sin(Util::deg2rad(angle)) * 25;
		gameObjects.push_back(new Projectile(spawnX, spawnY, angle, velocity + 600.0f));

		shootSound.play();
	}
	//printf("x = %f \n", x);
	if (x > 30000 && bossSpawned == false) {
		bossSpawned = true;
		printf("BOSS HAS SPAWNED\n");
		//boss = new Boss();
		gameObjects.push_back(boss);
	}
}

void Player::onCollide(GameObject* other) {
	// TODO
}

void Player::render() {
	setupTransformation();

	glRotatef(roll, 1, 0, 0);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture);

	GLint originalProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM, &originalProgram);
	glUseProgram(shader);

	glUniform1i(glGetUniformLocation(shader, "enableSimplification"), GL_TRUE);
	glUniform1f(glGetUniformLocation(shader, "simplifyGridSpacing"), Util::lerp(0.1f, 10.0f, 1.0f - health / 100.0f));

	static OBJModel lol("models/tiefighter.obj");
	lol.draw();

	glDisable(GL_TEXTURE_2D);

	glUseProgram(originalProgram);

	resetTransformation();
}
