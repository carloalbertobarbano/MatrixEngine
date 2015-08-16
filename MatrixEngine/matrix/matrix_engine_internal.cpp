#include "matrix_engine_internal.h"
#include "Shader.h"

using namespace MatrixEngine;
using namespace MatrixEngine::Graphics;

GLXSDLDevice *MatrixEngine::_pCurrentDevice = NULL;
GLXSDLCamera *MatrixEngine::_pCurrentCamera = NULL;

Scene::GLXSDLSceneGraph *MatrixEngine::Scene::_pCurrentSceneGraph  = NULL;
Graphics::TextureCube   *MatrixEngine::Graphics::_pCurrentTextureCube = NULL;

ofstream IOStream::error_stream;
ofstream IOStream::log_stream;

Shader::ShaderSource  *Graphics::framebuffer_vertex_shader = NULL, *Graphics::framebuffer_fragment_shader = NULL;
Shader::ShaderProgram *Graphics::framebuffer_shader = NULL;

void MatrixEngine::MatrixEngine_Init()
{
	IOStream::error_stream.open("error.log", ios::out);
	IOStream::log_stream.open("log.log", ios::out);

	IOStream::WriteOnStream("Initializing engine..", IOStream::log_stream);
	_pCurrentDevice = NULL;
}

void MatrixEngine::MatrixEngine_Quit()
{
	if (framebuffer_shader)
	{
		framebuffer_shader->detach_shader(framebuffer_vertex_shader);
		framebuffer_shader->detach_shader(framebuffer_fragment_shader);

		delete framebuffer_vertex_shader;
		delete framebuffer_fragment_shader;
		delete framebuffer_shader;
	}

	IOStream::WriteOnStream("Quitting engine..", IOStream::log_stream);
	IOStream::log_stream.close();
	IOStream::error_stream.close();
}

void IOStream::WriteOnStream(string s, ofstream &os)
{
	//cout << s.c_str() << endl;
	//TODO: Add output to in-game console
	os << s.c_str() << endl;
}

char* IOStream::textFileRead(string filen)
{
	char *text = NULL;

	if (filen.c_str() != NULL)
	{
		FILE *file = fopen(filen.c_str(), "rt");

		if (file != NULL) {
			fseek(file, 0, SEEK_END);
			int count = ftell(file);
			rewind(file);

			if (count > 0) {
				text = (char*)malloc(sizeof(char)*(count + 1));
				count = fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}
			fclose(file);
		}
	}
	return text;
}