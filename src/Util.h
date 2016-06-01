#pragma once

namespace Util {
	const float PI = 3.1415926535f;

	float rad2deg(float rad) {
		return rad / PI * 180.0f;
	}

	float deg2rad(float deg) {
		return deg / 180.0f * PI;
	}
}