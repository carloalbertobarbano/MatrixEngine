#include "GLXSDLSceneGraph.h"
#include "GLXSDLSceneEntity.h"

GLXSDLSceneGraph::GLXSDLSceneGraph()
{
	Scene::_pCurrentSceneGraph = this;
}

GLXSDLSceneGraph::~GLXSDLSceneGraph()
{
	cout << "Deleting scene graph.." << endl;

	for (int i = 0; i < nodes.size(); i++) {
		//if (nodes[i])
		 delete nodes[i];
	}

	//Scene::_pCurrentSceneGraph = NULL;
}

void GLXSDLSceneGraph::RenderScene() {
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->RenderThisAndSub();
	}
}