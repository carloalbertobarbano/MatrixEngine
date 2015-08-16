#include "Shader.h"

static void validateShader(GLuint shader, const char* file = 0)
{
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
	if (length > 0)
	{
		stringstream m;
		m << "Shader " << shader << " (" << (file ? file : " ") << ") compile error: " << buffer;
		WriteOnStream(m.str(), error_stream);
	}
}


static void validateProgram(GLuint program)
{
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;

	memset(buffer, 0, BUFFER_SIZE);
	glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
	if (length > 0)
	{
		stringstream m;
		m << "Program " << program << " ling error: " << buffer;
		WriteOnStream(m.str(), error_stream);
	}

	glValidateProgram(program);
	GLint status;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		stringstream m;
		m << "Error validating shader " << program;
		WriteOnStream(m.str(), error_stream);
	}
}

/***************SHADER SOURCE ***********************/

ShaderSource::ShaderSource()
{
	shader_handle = 0;
	init = false;
}

ShaderSource::~ShaderSource()
{
	if (init)
	{
		glDeleteShader(shader_handle);
	}
}

void ShaderSource::load_from_file(GLenum shader_type, string shader_file)
{
	cout << "------------------------------------" << endl << endl;
	cout << "Loading shader " << shader_file.c_str() << " from file.." << endl;

	char *source = textFileRead(shader_file);

	if (!source)
	{
		cout << "Shader file <" << shader_file.c_str() << "> not found!" << endl;
		return;
	}

	cout << "Shader loaded.." << endl;
	init_with_source(shader_type, source);
}

void ShaderSource::init_with_source(GLenum shader_type, const GLchar *source)
{
	cout << "Compiling shader.." << endl;
	shader_handle = glCreateShader(shader_type);
	cout << "\tShader created;" << endl;


	glShaderSource(shader_handle, 1, &source, 0);
	glCompileShader(shader_handle);
	cout << "\tShader compiled" << endl;

	char shader_info[512];
	GLsizei errors = 0;

	glGetShaderInfoLog(shader_handle, 512, &errors, shader_info);

	if (errors > 0)
	{
		stringstream m;
		m << "Shader compile error: " << shader_info << endl;
		WriteOnStream(m.str(), error_stream);
	}

	init = true;

	cout << "------------------------------------ SHADER ID: " << endl << endl;
}

uint ShaderSource::id()
{
	return shader_handle;
}
/****************SHADER PROGRAM ********************/

ShaderProgram::ShaderProgram()
{
	shader_id = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shader_id);
}

void ShaderProgram::attach_shader(ShaderSource *shader)
{
	glAttachShader(shader_id, shader->id());
}

void ShaderProgram::detach_shader(ShaderSource *shader)
{
	glDetachShader(shader_id, shader->id());
}

void ShaderProgram::compile()
{
	glLinkProgram(shader_id);
	validateProgram(shader_id);
}

unsigned int ShaderProgram::id()
{
	return shader_id;
}

void ShaderProgram::bind()
{
	glUseProgram(shader_id);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}


GLint ShaderProgram::getUniformLocation(const char *name)
{
	GLint loc = glGetUniformLocation(shader_id, name);
	if (loc < 0)
	{
		WriteOnStream("Cannot get location: " + string(name), error_stream);

	}
	return loc;
}

void ShaderProgram::sendUniform1f(GLint location, GLfloat v0)
{
	bind();
	glUniform1f(location, v0);
	unbind();
}

void ShaderProgram::sendUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	bind();
	glUniform2f(location, v0, v1);
	unbind();
}

void ShaderProgram::sendUniform2f(GLint location, vec2 v)
{
	bind();
	glUniform2f(location, v.x, v.y);
	unbind();
}

void ShaderProgram::sendUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	bind();
	glUniform3f(location, v0, v1, v2);
	unbind();
}

void ShaderProgram::sendUniform3f(GLint location, vec3 v)
{
	bind();
	glUniform3f(location, v.x, v.y, v.z);
	unbind();
}

void ShaderProgram::sendUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	bind();
	glUniform4f(location, v0, v1, v2, v3);
	unbind();
}

void ShaderProgram::sendUniform4f(GLint location, vec4 v)
{
	bind();
	glUniform4f(location, v.x, v.y, v.z, v.w);
	unbind();
}

void ShaderProgram::sendUniform1i(GLint location, GLint v0)
{
	bind();
	glUniform1i(location, v0);
	unbind();
}

void ShaderProgram::sendUniform2i(GLint location, GLint v0, GLint v1)
{
	bind();
	glUniform2i(location, v0, v1);
	unbind();
}

void ShaderProgram::sendUniform2i(GLint location, vec2 v)
{
	bind();
	int a[] = { v.x, v.y };
	glUniform2iv(location, 2, a);
	unbind();
}

void ShaderProgram::sendUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
	bind();
	glUniform3i(location, v0, v1, v2);
	unbind();
}

void ShaderProgram::sendUniform3i(GLint location, vec3 v)
{
	bind();
	sendUniform3i(location, v.x, v.y, v.z);
	unbind();
}

void ShaderProgram::sendUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	bind();
	glUniform4i(location, v0, v1, v2, v3);
	unbind();
}

void ShaderProgram::sendUniform4i(GLint location, vec4 v)
{
	bind();
	int a[] = { v.x, v.y, v.z, v.w };
	glUniform4iv(location, 4, a);
	unbind();
}

void ShaderProgram::sendUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix2fv(location, count, transpose, v);
	unbind();
}

void ShaderProgram::sendUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix2x3fv(location, count, transpose, v);
	unbind();
}

void ShaderProgram::sendUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix2x4fv(location, count, transpose, v);
	unbind();
}

void ShaderProgram::sendUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix3fv(location, count, transpose, v);
	unbind();
}

void ShaderProgram::sendUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix3x2fv(location, count, transpose, v);
	unbind();
}

void ShaderProgram::sendUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix3x4fv(location, count, transpose, v);
	unbind();
}

void ShaderProgram::sendUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, mat4 v)
{
	bind();
	glUniformMatrix4fv(location, count, transpose, glm::value_ptr(v));
	unbind();
}

void ShaderProgram::sendUniformMatrix4x2(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix4x2fv(location, count, transpose, v);
	unbind();
}

void ShaderProgram::sendUniformMatrix4x3(GLint location, GLsizei count, GLboolean transpose, GLfloat *v)
{
	bind();
	glUniformMatrix4x3fv(location, count, transpose, v);
	unbind();
}
//VERTEX ATTRIB

GLint ShaderProgram::getAttribLocation(const char *name)
{
	return glGetAttribLocation(shader_id, name);
}

void ShaderProgram::sendVertexAttrib1f(GLint location, GLfloat v0)
{
	bind();
	glVertexAttrib1f(location, v0);
	unbind();
}

void ShaderProgram::sendVertexAttrib2f(GLint location, GLfloat v0, GLfloat v1)
{
	bind();
	glVertexAttrib2f(location, v0, v1);
	unbind();
}

void ShaderProgram::sendVertexAttrib2f(GLint location, vec2 v)
{
	bind();
	glVertexAttrib2fv(location, glm::value_ptr(v));
	unbind();
}

void ShaderProgram::sendVertexAttrib3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	bind();
	glVertexAttrib3f(location, v0, v1, v2);
	unbind();
}

void ShaderProgram::sendVertexAttrib3f(GLint location, vec3 v)
{
	bind();
	glVertexAttrib3fv(location, glm::value_ptr(v));
	unbind();
}

void ShaderProgram::sendVertexAttrib4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	bind();
	glVertexAttrib4f(location, v0, v1, v2, v3);
	unbind();
}

void ShaderProgram::sendVertexAttrib4f(GLint location, vec4 v)
{
	bind();
	glVertexAttrib4fv(location, glm::value_ptr(v));
	unbind();
}

/*void Shader::sendVertexAttrib1i(GLint location,GLint v0)
{
glLinkProgram(shader_id);
glUseProgram(shader_id);
glVertexAttrib1f(location,v0);
}

void Shader::sendVertexAttrib2i(GLint location,GLint v0,GLint v1)
{
glLinkProgram(shader_id);
glUseProgram(shader_id);
glVertexAttrib2i(location,v0,v1);
}

void Shader::sendVertexAttrib2i(GLint location,Vec2 v)
{
glLinkProgram(shader_id);
glUseProgram(shader_id);
glVertexAttrib2iv(location,2,v);
}

void Shader::sendVertexAttrib3i(GLint location,GLint v0,GLint v1,GLint v2)
{
glLinkProgram(shader_id);
glUseProgram(shader_id);
glVertexAttrib3i(location,v0,v1,v2);
}

void Shader::sendVertexAttrib3i(GLint location,Vec3 v)
{
glLinkProgram(shader_id);
glUseProgram(shader_id);
glVertexAttribiv(location,3,v);
}

void Shader::sendVertexAttrib4i(GLint location,GLint v0,GLint v1,GLint v2,GLint v3)
{
glLinkProgram(shader_id);
glUseProgram(shader_id);
glVertexAttrib4i(location,v0,v1,v2,v3);
}

void Shader::sendVertexAttrib4i(GLint location,Vec4 v)
{
glLinkProgram(shader_id);
glUseProgram(shader_id);
glVertexAttrib4iv(location,4,v);
}*/









