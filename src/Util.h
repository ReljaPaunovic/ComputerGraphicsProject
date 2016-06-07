#pragma once

#include <string>
#include <fstream>
#include <vector>

namespace Util {
	const float PI = 3.1415926535f;

	inline float rad2deg(float rad) {
		return rad / PI * 180.0f;
	}

	inline float deg2rad(float deg) {
		return deg / 180.0f * PI;
	}

	inline std::string readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate);

		size_t fileSize = (size_t) file.tellg();
		std::vector<char> fileData(fileSize);

		file.seekg(0, std::ios::beg);
		file.read(fileData.data(), fileSize);
		file.close();

		fileData.push_back(0);

		return fileData.data();
	}
}