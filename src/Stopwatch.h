#pragma once

#include <chrono>

class Stopwatch {
public:
	Stopwatch() {
		restart();
	}

	void restart() {
		startTime = std::chrono::high_resolution_clock::now();
	}

	float time() {
		auto timeNow = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(timeNow - startTime).count() / 1e6f;
	}

private:
	std::chrono::steady_clock::time_point startTime;
};