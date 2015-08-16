#ifndef SHADER_H
#define SHADER_H

#include "matrix_engine_internal.h"

using namespace MatrixEngine;
using namespace MatrixEngine::IOStream;
using namespace MatrixEngine::Shader;

using namespace glm;

class Shader::ShaderSource
{
public:
	ShaderSource();
	~ShaderSource();

	void load_from_file(GLenum shader_type, string shader_file);
	void init_with_source(GLenum shader_type, const GLchar *shader_source);

	uint id();
protected:
	GLuint shader_handle;
	bool init;
};

class Shader::ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();


	void attach_shader(ShaderSource *shader);
	void detach_shader(ShaderSource *shader);
	void compile();
	void bind();
	void unbind();

	uint id();

	GLint getUniformLocation(const char *name);

	void sendUniform1f(GLint location, GLfloat v0);
	void sendUniform2f(GLint location, GLfloat v0, GLfloat v1);
	void sendUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	void sendUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void sendUniform2f(GLint location, vec2 v);
	void sendUniform3f(GLint location, vec3 v);
	void sendUniform4f(GLint location, vec4 v);

	void sendUniform1i(GLint location, GLint v0);
	void sendUniform2i(GLint location, GLint v0, GLint v1);
	void sendUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
	void sendUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	void sendUniform2i(GLint location, vec2 v);
	void sendUniform3i(GLint location, vec3 v);
	void sendUniform4i(GLint location, vec4 v);

	void sendUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
	void sendUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
	void sendUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
	void sendUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
	void sendUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
	void sendUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
	void sendUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, mat4 v);
	void sendUniformMatrix4x2(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);
	void sendUniformMatrix4x3(GLint location, GLsizei count, GLboolean transpose, GLfloat *v);

	GLint getAttribLocation(const char *name);

	void sendVertexAttrib1f(GLint location, GLfloat v0);
	void sendVertexAttrib2f(GLint location, GLfloat v0, GLfloat v1);
	void sendVertexAttrib3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	void sendVertexAttrib4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void sendVertexAttrib2f(GLint location, vec2 v);
	void sendVertexAttrib3f(GLint location, vec3 v);
	void sendVertexAttrib4f(GLint location, vec4 v);

	void sendVertexAttrib1i(GLint location, GLint v0);
	void sendVertexAttrib2i(GLint location, GLint v0, GLint v1);
	void sendVertexAttrib3i(GLint location, GLint v0, GLint v1, GLint v2);
	void sendVertexAttrib4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	void sendVertexAttrib2i(GLint location, vec2 v);
	void sendVertexAttrib3i(GLint location, vec3 v);
	void sendVertexAttrib4i(GLint location, vec4 v);

protected:
	uint shader_id;

	bool first_init;
};


#endif
