#ifndef MATRIX_ENGINE_INTERNAL_H
#define MATRIX_ENGINE_INTERNAL_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#define GLM_FORCE_INLINE
#include <glm\glm.hpp>

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

#include <glm\mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\constants.hpp>

#include <glew\glew.h>

#include <SDL\SDL.h>
#include <SDL_image\SDL_image.h>

#define NO_SDL_GLEXT
#include <SDL\SDL_opengl.h>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#define PI 3.141592653589793

using namespace std;

namespace MatrixEngine {
	extern void MatrixEngine_Init();
	extern void MatrixEngine_Quit();

	//typedef unsigned int uint;

	namespace IOStream {
		extern ofstream error_stream;
		extern ofstream log_stream;

		extern void WriteOnStream(string s, ofstream &os);
		extern char *textFileRead(string file);
	}

	class GLXSDLDevice;
	class GLXSDLRenderPipeline;
	class GLXSDLCamera;
	
	namespace Scene {
		class GLXSDLSceneGraph;
		class GLXSDLSceneEntity;
		class GLXSDLSceneInstance;

		extern GLXSDLSceneGraph *_pCurrentSceneGraph;
		

		namespace Components {
			class Mesh;
		}
	}

	namespace Shader {
		class ShaderSource;
		class ShaderProgram;
	}

	namespace Graphics {
		class Texture;
		class TextureCube;
		class Material;
		class Light;
		class VAO;
		class FrameBufferObject;

		extern Shader::ShaderSource *framebuffer_vertex_shader, *framebuffer_fragment_shader;
		extern Shader::ShaderProgram *framebuffer_shader;
		extern TextureCube *_pCurrentTextureCube;

		namespace Render {
			class MeshRenderer;
		}
	}

	namespace Devices {
		class Keyboard;
		class Mouse;
	}

	extern GLXSDLDevice *_pCurrentDevice;
	extern GLXSDLCamera *_pCurrentCamera;
}

#endif