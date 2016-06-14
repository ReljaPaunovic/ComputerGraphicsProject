#pragma once

#include <string>
#include <fstream>
#include <vector>

namespace Util {
	const float pi = 3.1415926535f;

	inline float rad2deg(float rad) {
		return rad / pi * 180.0f;
	}

	inline float deg2rad(float deg) {
		return deg / 180.0f * pi;
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

	inline GLuint loadTexture(const std::string& filename, bool pixelated = false) {
		GLuint texture;

		int textureWidth, textureHeight;
		int textureComponents;
		stbi_uc* pixels = stbi_load(filename.c_str(), &textureWidth, &textureHeight, &textureComponents, STBI_rgb_alpha);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(pixels);

		return texture;
	}

	inline void drawTexturedQuad(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& uv1, const glm::vec2& uv2) {
		glBegin(GL_QUADS);
			glTexCoord2f(uv1.x, uv1.y);
			glVertex2f(p1.x, p1.y);

			glTexCoord2f(uv2.x, uv1.y);
			glVertex2f(p2.x, p1.y);

			glTexCoord2f(uv2.x, uv2.y);
			glVertex2f(p2.x, p2.y);

			glTexCoord2f(uv1.x, uv2.y);
			glVertex2f(p1.x, p2.y);
		glEnd();
	}
}