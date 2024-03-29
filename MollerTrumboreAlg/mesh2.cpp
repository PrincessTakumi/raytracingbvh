#include "mesh2.h"

Mesh::Mesh(const std::string &file, const vec3 &off) : offset(off)
{
	importFile(file);
	for (int i = 0; i < m_numfaces; i++)
		triangles.push_back(new Triangle(
			vertices.at(indices.at(3 * i)),
			vertices.at(indices.at(3 * i + 1)),
			vertices.at(indices.at(3 * i + 2)),
			new metal(vec3(0.25, 0.25, 0.25) ,0)));
			//new dielectric(1.5)));
			//new lambertian(vec3(0.6, 0.2, 0.2))));
}

bool Mesh::importFile(const std::string &file)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(file,
		aiProcessPreset_TargetRealtime_Quality  |
		aiProcess_Triangulate					|
		aiProcess_SortByPType					|
		aiProcess_JoinIdenticalVertices			|
		aiProcess_GenNormals					|
		aiProcess_FixInfacingNormals			);

	if (!scene)
		return false;
	else processData(scene);
	return true;
} 

bool Mesh::getMeshData(const aiMesh*mesh)
{
	aiFace *face;

	for (int v = 0; v < mesh->mNumVertices; v++)
		vertices.push_back(vec3(
			mesh->mVertices[v].x, 
			mesh->mVertices[v].y, 
			mesh->mVertices[v].z) + offset);

	m_numfaces = mesh->mNumFaces;
	for (int f = 0; f < mesh->mNumFaces; f++)
	{
		face = &mesh->mFaces[f];
		indices.push_back(face->mIndices[0]);
		indices.push_back(face->mIndices[1]);
		indices.push_back(face->mIndices[2]);
	}

	return true;
}

bool Mesh::processData(const aiScene* scene)
{
	bool repeat = true;

	std::vector<const aiNode* > nodeBuff;
	const aiNode* modelNode;

	nodeBuff.push_back(scene->mRootNode);

	while (repeat)
	{
		for (int a = 0; a < nodeBuff.size(); a++)
		{
			modelNode = nodeBuff.at(a);
			if (modelNode->mNumChildren > 0)
				for (int c = 0; c < modelNode->mNumChildren; c++)
					nodeBuff.push_back(modelNode->mChildren[c]);

			else repeat = false;
		}
	}

	for (int a = 0; a < nodeBuff.size(); a++)
	{
		modelNode = nodeBuff.at(a);

		if (modelNode->mNumMeshes > 0)
		{
			for (int b = 0; b < modelNode->mNumMeshes; b++)
				getMeshData(scene->mMeshes[b]);
		}
	}

	return true;
}