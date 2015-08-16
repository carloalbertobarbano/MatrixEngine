#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "matrix_engine_internal.h"
#include "GLXSDLSceneInstance.h"

using namespace MatrixEngine;
using namespace MatrixEngine::Scene;
using namespace MatrixEngine::Graphics;
using namespace MatrixEngine::Graphics::Render;
using namespace MatrixEngine::Shader;

class Render::MeshRenderer : public Scene::GLXSDLSceneInstance {
	public :
		MeshRenderer(Scene::Components::Mesh *mesh);
		~MeshRenderer();

		inline void SetMeshAsset(Components::Mesh *mesh){ _pMeshAsset = mesh; };
		
		void LoadShader(string vs, string fs, string gs = "");

		void Update() { }
		void Render();

	protected :
		ShaderProgram *shader;
		ShaderSource  *shader_vert, *shader_frag, *shader_geom;

		Components::Mesh *_pMeshAsset;
};


#endif