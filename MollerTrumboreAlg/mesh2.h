#ifndef MESH2H
#define MESH2H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

#include "vec3.h"
#include "material.h"
#include "algorithm.h"

class Mesh
{
public:
	Mesh(const std::string & file, const vec3 &off);

	bool importFile(const std::string &file);
	bool getMeshData(const aiMesh *mesh);
	bool processData(const aiScene* scene);
	

	int m_numfaces;
	std::vector<vec3> vertices;
	std::vector<int> indices;
	std::vector<Triangle*> triangles;
	vec3 offset;
};

#endif