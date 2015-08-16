#ifndef GL_SCENE_ENTITY_H
#define GL_SCENE_ENTITY_H

#include "matrix_engine_internal.h"
#include "GLXSDLSceneInstance.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace MatrixEngine;
using namespace MatrixEngine::Scene;
using namespace std;


/******************************************************************/
/* GLXSDLSceneEntity represents a non-drawable oject of the scene */
/* which has a pointer to GLXSDLSceneInstance which is drawable   */
/******************************************************************/

class Scene::GLXSDLSceneEntity {
	public :
		GLXSDLSceneEntity(GLXSDLSceneInstance *_instance = NULL, string name = "");
		~GLXSDLSceneEntity();

		void AddChild(GLXSDLSceneEntity *child);
		inline void RemoveChild(GLXSDLSceneEntity *child){ children.erase(std::remove(children.begin(), children.end(), child), children.end()); }

		
		inline GLXSDLSceneEntity *GetParent(){ return parent; }

		inline int GetChildrenCount(){ return children.size(); }
		inline GLXSDLSceneEntity *GetChild(int index){ return children[index]; }
		
		inline void SetInstance(GLXSDLSceneInstance *_instance){ instance = _instance;  
																 instance->entity = this; }

		inline GLXSDLSceneInstance *GetInstance(){ return instance; }

		void setNodeName(string name){ node_name = name; }
		string getNodeName(){ return node_name;  }

		void RenderInstance();
		void RenderThisAndSub(int level = -1);

		void translate(glm::vec3 p);
		void rotate(float angle, float x, float y, float z);
		void scale(glm::vec3 s);
		void buildTransformMatrix();

		inline glm::vec3 getPosition(){ return pos; }
		inline glm::mat4 getTransofrmMatrix(){ return transformMatrix; }

	protected :
		string node_name;

		Scene::GLXSDLSceneInstance *instance;
		GLXSDLSceneEntity *parent; 
		std::vector < GLXSDLSceneEntity *> children;

		glm::vec3 pos;
		glm::vec3 rot;
		glm::vec3 scaleVec;
		float angle;
		glm::mat4 transformMatrix;

		void SetParent(GLXSDLSceneEntity *_parent);

};

#endif // !GL_SCENE_ENTITY_H
