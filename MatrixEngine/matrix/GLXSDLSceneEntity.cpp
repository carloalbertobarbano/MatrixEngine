#include "GLXSDLSceneEntity.h"
#include "GLXSDLSceneInstance.h"
#include "GLXSDLSceneGraph.h"

GLXSDLSceneEntity::GLXSDLSceneEntity(GLXSDLSceneInstance *_instance, string name)
{
	this->SetInstance(_instance);

	parent = NULL;
	
	if (name == "" && _pCurrentSceneGraph){
		stringstream ss;

		ss << "node" << _pCurrentSceneGraph->GetNodesCount();
		node_name = ss.str();
	}
	else {
		node_name = name;
	}
}

GLXSDLSceneEntity::~GLXSDLSceneEntity()
{
	cout << "Deleting " << node_name << endl;

	if (instance) {
		delete instance;
		cout << "Deleting Instance for " << node_name << endl;
	}

	for (int i = 0; i < children.size(); i++){
		if (children[i])
			delete children[i];
	}
}

void GLXSDLSceneEntity::SetParent(GLXSDLSceneEntity *_parent)
{
	parent = _parent;

	if (parent){
		stringstream ss;
		//ss << "child " << parent->GetChildrenCount();
		node_name = ss.str() + "" + node_name;
	}
}

void GLXSDLSceneEntity::AddChild(GLXSDLSceneEntity *child)
{
	children.push_back(child);
	children[GetChildrenCount() - 1]->SetParent(this);
}

void GLXSDLSceneEntity::translate(glm::vec3 p)
{
	pos = p;
}

void GLXSDLSceneEntity::rotate(float a, float x, float y, float z)
{
	rot = glm::vec3(x, y, z);
	angle = a;
}

void GLXSDLSceneEntity::scale(glm::vec3 s)
{
	scaleVec = s;
}

void GLXSDLSceneEntity::buildTransformMatrix()
{
	transformMatrix = glm::mat4(1);
	transformMatrix = glm::translate(transformMatrix, pos);
	transformMatrix = glm::rotate(transformMatrix, angle, rot);
	transformMatrix = glm::scale(transformMatrix, scaleVec);
}

void GLXSDLSceneEntity::RenderInstance() {
	if (instance) {
		instance->Render();
	}
}

void GLXSDLSceneEntity::RenderThisAndSub(int level) {
	if (level <= 0 || level > children.size()) {
		level = children.size();
	}

	RenderInstance();

	for (int i = 0; i < level; i++) {
		children[i]->RenderThisAndSub();
	}
}