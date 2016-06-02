#pragma once

enum ColliderType {
	CIRCLE,
	RECTANGLE
};

class Collider {
	Collider(int radius) {
		type = CIRCLE;
	}

	Collider(int width, int height) {
		type = RECTANGLE;
	}

	ColliderType type;
};
