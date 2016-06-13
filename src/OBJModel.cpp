#include "OBJModel.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>

OBJModel::OBJModel(const std::string& filename) {
	loadData(filename);
	buildDisplayList();
}

void OBJModel::draw() const {
	glCallList(displayList);
}

void OBJModel::loadData(const std::string& filename) {
	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream str(line);

		if (str.peek() == 'v') {
			std::string command;
			str >> command;

			if (command == "v") {
				glm::vec3 pos;
				str >> pos.x;
				str >> pos.y;
				str >> pos.z;
				positions.push_back(pos);
			} else if (command == "vt") {
				glm::vec2 texcoord;
				str >> texcoord.x;
				str >> texcoord.y;
				texcoords.push_back(texcoord);
			} else if (command == "vn") {
				glm::vec3 norm;
				str >> norm.x;
				str >> norm.y;
				str >> norm.z;
				normals.push_back(norm);
			}
		} else if (str.peek() == 'f') {
			// check which indices are included (of the possible pos, texcoord, normal)
			// pos is mandatory, of course
			size_t elements = (std::count(line.begin(), line.end(), '/') / 3) + 1;

			str >> line; // discard command

			std::array<glm::ivec3, 3> tri;

			for (int i = 0; i < 3; i++) {
				glm::ivec3 vertex(0, 0, 0);

				str >> vertex.x;
				if (elements >= 2) { str.ignore(1); /* discard slash */ str >> vertex.y; }
				if (elements >= 3) { str.ignore(1); /* discard slash */ str >> vertex.z; }

				// Indices are 1-based
				tri[i] = vertex - glm::ivec3(1, 1, 1);
			}

			triangles.push_back(tri);
		}
	}

	std::cerr << "finished loading model " << filename << std::endl;
	std::cerr << "\t#positions = " << positions.size() << std::endl;
	std::cerr << "\t#texcoords = " << texcoords.size() << std::endl;
	std::cerr << "\t#normals = " << normals.size() << std::endl;
	std::cerr << "\t#triangles = " << triangles.size() << std::endl;
}

void OBJModel::buildDisplayList() {
	displayList = glGenLists(1);

	glNewList(displayList, GL_COMPILE);
	
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);

	for (int i = 0; i < triangles.size(); i++) {
		for (int j = 0; j < 3; j++) {
			glm::ivec3 vertex = triangles[i][j];

			if (vertex.y != -1) glTexCoord2f(texcoords[vertex.y].s, texcoords[vertex.y].t);
			if (vertex.z != -1) glNormal3f(normals[vertex.z].x, normals[vertex.z].y, normals[vertex.z].z);
			glVertex3f(positions[vertex.x].x, positions[vertex.x].y, positions[vertex.x].z);
		}
	}

	glEnd();

	glEndList();
}