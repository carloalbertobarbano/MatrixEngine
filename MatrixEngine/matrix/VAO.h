#ifndef GL3_VAO_H
#define GL3_VAO_H

#include "matrix_engine_internal.h"

using namespace MatrixEngine;
using namespace MatrixEngine::Graphics;

class Graphics::VAO
{
public :
	VAO();
	~VAO();

	void Construct(int buff_n);
	void BufferData(int buff,GLenum target,GLsizeiptr size,GLvoid *data,GLenum mode);
	void VertexAttribute(int location,int size,GLenum type,GLboolean normalize,GLsizei stride,GLvoid *pointer);
	void DeleteBuffer(int buff_n);
	void GenBuffer(int buff_n);
	void ResetBuffer(int buff_n);

	void bind();
	void unbind();

	void DrawArrays(GLenum mode,GLint first,GLsizei count,void *indices = NULL);

	int vert_count;
	bool constructed;
protected :
	GLuint *buffer;
	GLuint vao;
};

#endif
