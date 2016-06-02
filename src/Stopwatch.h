#pragma once

#include <ctime>

class Stopwatch {
public:
	Stopwatch() {
		restart();
	}

	void restart() {
		startTime = clock();;
	}

	float time() {
		return (clock() - startTime) / (float) CLOCKS_PER_SEC;
	}

private:
	clock_t startTime;
};