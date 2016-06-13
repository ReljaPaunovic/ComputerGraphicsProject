#pragma once

#include <vector>
#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

// TODO: Use display list for drawing
class OBJModel {
public:
	OBJModel(const std::string& filename);

	void draw() const;

private:
	std::vector<std::array<glm::ivec3, 3>> triangles; // 3 vertices with pos, tex, normal order
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;

	void loadData(const std::string& filename);
};