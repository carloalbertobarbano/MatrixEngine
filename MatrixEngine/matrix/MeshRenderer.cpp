#include "MeshRenderer.h"
#include "Shader.h"
#include "GLXSDLSceneEntity.h"
#include "GLXSDLRenderPipeline.h"
#include "GLXSDLCamera.h"
#include "Texture.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer(Components::Mesh *mesh) : GLXSDLSceneInstance() {
	SetMeshAsset(mesh);
	shader = NULL;
}

MeshRenderer::~MeshRenderer()
{

	if (shader)
	{
		shader->detach_shader(shader_vert);
		if (shader_geom)shader->detach_shader(shader_geom);
		shader->detach_shader(shader_frag);

		delete shader_vert;
		if (shader_geom)delete shader_geom;
		delete shader_frag;
		delete shader;
	}
}


void MeshRenderer::LoadShader(string vs, string fs, string gs)
{
	shader_vert = new ShaderSource();
	shader_frag = new ShaderSource();
	if (gs != "")shader_geom = new ShaderSource();
	shader = new ShaderProgram();

	shader_vert->load_from_file(GL_VERTEX_SHADER, vs);
	shader_frag->load_from_file(GL_FRAGMENT_SHADER, fs);
	if (gs != "")shader_geom->load_from_file(GL_GEOMETRY_SHADER, gs);


	shader->attach_shader(shader_vert);
	if (gs != "")shader->attach_shader(shader_geom);
	shader->attach_shader(shader_frag);
	shader->compile();
}

void MeshRenderer::Render() {
	
	entity->buildTransformMatrix();
	mat4 transformMatrix = entity->getTransofrmMatrix();

	if (shader) {
		shader->sendUniformMatrix4fv(shader->getUniformLocation("projMat"), 1, GL_FALSE, GLXSDLRenderPipeline::glProjectionMatrix);
		shader->sendUniformMatrix4fv(shader->getUniformLocation("viewMat"), 1, GL_FALSE, GLXSDLRenderPipeline::glViewMatrix);
		shader->sendUniformMatrix4fv(shader->getUniformLocation("modMat"), 1, GL_FALSE, transformMatrix);
		shader->sendUniform1i(shader->getUniformLocation("diffuse_texture"), 0);
		shader->sendUniform1i(shader->getUniformLocation("cubemap"), 1);
		shader->sendUniform1i(shader->getUniformLocation("texture_bump"), 2);

		vec3 camera_pos = -MatrixEngine::_pCurrentCamera->GetPosition();

		shader->sendUniform3f(shader->getUniformLocation("camera_position"), camera_pos);

		/*if (Graphics::_pCurrentTextureCube)
		{
			glEnable(GL_TEXTURE_CUBE_MAP);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, Graphics::_pCurrentTextureCube->get_texture());
		}*/

		if (GLXSDLRenderPipeline::ShadeMode == GLXSDLRenderPipeline::COLOR)
		{
			shader->sendUniform1i(shader->getUniformLocation("render_all_with_color"), 1);
			shader->sendUniform4f(shader->getUniformLocation("color"), GLXSDLRenderPipeline::color);
		}
		else
		{
			shader->sendUniform1i(shader->getUniformLocation("render_all_with_color"), 0);
		}
	}

	for (int i = 0; i < _pMeshAsset->sections.size(); i++) {
		if (shader){
			shader->bind();
			_pMeshAsset->sections[i].material.sendMaterialUniforms(shader);
			_pMeshAsset->sections[i].material.texture_diffuse.bind_unit(0);
			_pMeshAsset->sections[i].material.texture_bump.bind_unit(2);
		}


		_pMeshAsset->sections[i].Render();

		if (shader){
			shader->unbind();
			_pMeshAsset->sections[i].material.texture_diffuse.unbind();
			_pMeshAsset->sections[i].material.texture_bump.unbind();
		}
	}

}