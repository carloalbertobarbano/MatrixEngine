#ifndef GL_SCENE_GRAPH_H
#define GL_SCENE_GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "matrix_engine_internal.h"

using namespace std;
using namespace MatrixEngine;
using namespace MatrixEngine::Scene;

class Scene::GLXSDLSceneGraph {
	public :
		GLXSDLSceneGraph();
		~GLXSDLSceneGraph();

		inline void AddEntityNode(GLXSDLSceneEntity *node){ nodes.push_back(node); }
		inline void RemoveEntityNode(GLXSDLSceneEntity *node){ nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end()); }
		
		inline int GetNodesCount(){ return nodes.size(); }

		inline std::vector<GLXSDLSceneEntity *> *GetNodes(){ return &nodes; }
		inline GLXSDLSceneEntity *GetNode(int index){ return nodes[index]; }

		void RenderScene();

	protected :
		std::vector<GLXSDLSceneEntity*> nodes;
};

#endif