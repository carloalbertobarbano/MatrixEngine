#ifndef GL3_MATERIAL_H
#define GL3_MATERIAL_H

#include "matrix_engine_internal.h"
#include "Shader.h"
#include "Texture.h"

using namespace MatrixEngine;
using namespace MatrixEngine::Graphics;
using namespace MatrixEngine::Shader;


class Graphics::Material
{
public:
	Material();

	void sendMaterialUniforms(ShaderProgram *shader);

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	int  shininess;

	Texture texture;
	Texture texture_diffuse;
	Texture texture_specular_color;
	Texture texture_specular_highlight;
	Texture texture_alpha;
	Texture texture_bump;

	bool reflection;
	bool refraction;
	bool emissive;

	string name;

	struct{
		int material_ambient;
		int material_diffuse;
		int material_specular;
		int material_shininess;

		int texture;
		int texture_diffuse;
		int texture_specular_color;
		int texture_specular_highlight;
		int texture_alpha;
		int texture_bump;

		int use_texture;
		int use_reflection;
		int use_refraction;
		int emissive;

		int render_all_with_color;
		int color;

		bool constructed;
	}locations;
};

#endif