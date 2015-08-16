#ifndef GL_SCENE_INSTANCE_H
#define GL_SCENE_INSTANCE_H

#include "matrix_engine_internal.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace MatrixEngine;
using namespace MatrixEngine::Scene;
using namespace std;


class Scene::GLXSDLSceneInstance {
	public :
		GLXSDLSceneInstance(){ };
		
		virtual void Update(){ }
		virtual void Render(){ }

	protected :
		friend class Scene::GLXSDLSceneEntity;

		GLXSDLSceneEntity *entity;
};

#endif