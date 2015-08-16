#include "GLXSDLRenderPipeline.h"
#include "Shader.h"

using namespace MatrixEngine;
using namespace MatrixEngine::IOStream;
using namespace MatrixEngine::Graphics;

uint GLXSDLRenderPipeline::clear_screen_list_start = 0;
bool GLXSDLRenderPipeline::constructed = false;

mat4 GLXSDLRenderPipeline::glProjectionMatrix;
mat4 GLXSDLRenderPipeline::glViewMatrix;

int  GLXSDLRenderPipeline::RenderMode = RENDER_ALL;
int  GLXSDLRenderPipeline::FillMode = FILL_SOLID;
int  GLXSDLRenderPipeline::ShadeMode = LIGHTING;

vec4  GLXSDLRenderPipeline::color = vec4(0.7, 0.7, 0.7, 1.0);

float GLXSDLRenderPipeline::DistanceForBumpMapping = 10.0;

bool GLXSDLRenderPipeline::Construct()
{
	WriteOnStream("Genarating clear screen list..", log_stream);

	clear_screen_list_start = glGenLists(1);
	glNewList(clear_screen_list_start, GL_COMPILE);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEndList();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);



	glEnable(GL_TEXTURE_2D);

	glProjectionMatrix = glm::mat4(); // LoadIdentity();
	glViewMatrix = glm::mat4(); // LoadIdentity();

	WriteOnStream("Creating default framebuffer shader", log_stream);

	framebuffer_shader = new ShaderProgram();
	framebuffer_vertex_shader = new ShaderSource();
	framebuffer_fragment_shader = new ShaderSource();



	framebuffer_vertex_shader->load_from_file(GL_VERTEX_SHADER, "data/shader/fbo_shader.vert");
	framebuffer_fragment_shader->load_from_file(GL_FRAGMENT_SHADER, "data/shader/fbo_shader.frag");

	framebuffer_shader->attach_shader(framebuffer_vertex_shader);
	framebuffer_shader->attach_shader(framebuffer_fragment_shader);
	framebuffer_shader->compile();

	constructed = true;

	return true;
}

void GLXSDLRenderPipeline::ClearScreen(vec4 color)
{
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(color.x, color.y, color.z, color.w);
}

void GLXSDLRenderPipeline::SetProjectionMatrix(int view_angle, float near_plane, float far_plane, float ratio)
{
	if (ratio == -1)
	{
		ratio = _pCurrentDevice->GetResolution().x / _pCurrentDevice->GetResolution().y; // GetRatio();
	}

	glProjectionMatrix = glm::perspective((float)view_angle, ratio, near_plane, far_plane);
	//glProjectionMatrix.buildProjection(view_angle, ratio, near_plane, far_plane);
}

void GLXSDLRenderPipeline::ResetViewMatrix()
{
	glViewMatrix = glm::mat4(); // LoadIdentity();
}

void GLXSDLRenderPipeline::PrepareForRendering()
{
	SetViewport();
	SetProjectionMatrix();
	ResetViewMatrix();
}
