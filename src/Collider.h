#pragma once
enum ColliderType {
	CIRCLE,
	RECTANGLE
};

class Collider {

public:
	Collider(int radius) {
		type = CIRCLE;
		r = radius;
	}

	Collider(int width, int height) {
		type = RECTANGLE;
	}

	double r = 0;
	double width = 0;
	double height = 0;
	ColliderType type;
};