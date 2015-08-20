#include <iostream>

#ifdef WIN32

#include "matrix\MatrixEngine.h"

#else
#include "matrix/MatrixEngine.h"


#endif // WIN32

using namespace std;

using namespace MatrixEngine;
using namespace MatrixEngine::Graphics;

bool running = true;

void EventHandler();

void PrintChildren(GLXSDLSceneEntity *node);

int main(int arcg, char **argv){

	MatrixEngine::MatrixEngine_Init();

	GLXSDLDevice device;
	device.Construct(SDL_INIT_EVERYTHING, glm::vec3(800, 600, 32), false);
	device.SetCaption("Matrix Engine");


	GLXSDLSceneGraph *sceneGraph = new GLXSDLSceneGraph();

	GLXSDLSceneInstance *instance = new GLXSDLSceneInstance();
	GLXSDLSceneEntity *node = new GLXSDLSceneEntity(instance);
	sceneGraph->AddEntityNode(node);

	node->AddChild(new GLXSDLSceneEntity(new GLXSDLSceneInstance(),"a"));
	node->GetChild(0)->AddChild(new GLXSDLSceneEntity(new GLXSDLSceneInstance(), "subchild"));
	node->GetChild(0)->GetChild(0)->AddChild(new GLXSDLSceneEntity(new GLXSDLSceneInstance(), "sub-sub-child"));

	node->AddChild(new GLXSDLSceneEntity(new GLXSDLSceneInstance(),"b"));
	node->AddChild(new GLXSDLSceneEntity(new GLXSDLSceneInstance(),"c"));
	node->AddChild(new GLXSDLSceneEntity(new GLXSDLSceneInstance(),"d"));


	/*********************************************************************************/
	/* Mesh is the model asset *******************************************************/
	/* The SceneEntity is the model instance, wich has the MeshRenderer as instance, */
	/* that renders the mesh asset ***************************************************/
	/*********************************************************************************/

	Components::Mesh *mesh = new Components::Mesh();
	mesh->LoadFromFile("data/models/test.obj");

	Render::MeshRenderer *renderer = new Render::MeshRenderer(mesh);
	renderer->LoadShader("data/shader/default_model.vs", "data/shader/default_model.fs");

	GLXSDLSceneEntity *node2 = new GLXSDLSceneEntity(renderer,"MeshRenderer1");
	node2->translate(vec3(0.0, 0.0, -10.0));
	node2->rotate(0.0, 1.0, 1.0, 1.0);
	node2->scale(vec3(1.0, 1.0, 1.0));

	sceneGraph->AddEntityNode(node2);

	cout << "Scene nodes count: " << sceneGraph->GetNodesCount() << endl << endl << endl;

	for (int i = 0; i < sceneGraph->GetNodesCount(); i++){
		cout << "Node " << i << ": " << sceneGraph->GetNode(i)->getNodeName() << endl;
		PrintChildren(sceneGraph->GetNode(i));
	}

	cout << endl << endl << endl;

	cout << "Now rendering" << endl;

    GLXSDLCamera *camera = new GLXSDLCamera();
    camera->SetPosition(vec3(0.0,0.0,0.0));

	while (running)
	{
		EventHandler();

		GLXSDLRenderPipeline::PrepareForRendering();
		GLXSDLRenderPipeline::ClearScreen(vec4(0.0, 0.0, 1.0, 1.0));

        camera->ApplyTransform();

		sceneGraph->RenderScene();

		GLXSDLRenderPipeline::SwapBuffer();
	}

    delete camera;
	delete mesh;
	delete sceneGraph;


	MatrixEngine::MatrixEngine_Quit();
	return 0;
}

void EventHandler()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			running = false;
		}
			break;

		case SDL_KEYDOWN:
		{

		    //keyboard.key[event.key.keysym.sym] = true;

		    switch (event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					running = false;
					break;

				default:break;
			}
		}
			break;

		case SDL_KEYUP:
		{
			//keyboard.key[event.key.keysym.sym] = false;
		}
			break;

		default: break;
		}
	}
}

void PrintChildren(GLXSDLSceneEntity *node)
{
	for (int i = 0; i < node->GetChildrenCount(); i++) {
		cout << "|" << endl;
		cout << "|-- Child " << i << ": " << node->GetChild(i)->getNodeName() << endl;

		PrintChildren(node->GetChild(i));
	}
}
