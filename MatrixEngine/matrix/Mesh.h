#ifndef MESH_H
#define MESH_H

#include "matrix_engine_internal.h"
#include "Material.h"
#include "VAO.h"


#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


using namespace Assimp;

using namespace MatrixEngine;
using namespace MatrixEngine::Scene;
using namespace MatrixEngine::Scene::Components;

using namespace glm;

class MeshSection {
	public :
		std::vector<vec3> vert;
		std::vector<vec3> norm;
		std::vector<vec2> tex_coord;
		std::vector<vec3> tang;
		std::vector<int> indices;

		Material material;
		VAO vao;

		void ConstructVAO();
		void Render();
};


class Components::Mesh {
	public :
		Mesh();

		void LoadFromFile(string file);

		
	protected :
		std::vector<MeshSection> sections;
		
		friend class MatrixEngine::Graphics::Render::MeshRenderer;

	private :
		void processNode(aiNode *node, const aiScene *scene);
		void processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif