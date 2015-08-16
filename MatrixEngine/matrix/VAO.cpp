#include "VAO.h"

VAO::VAO()
{
	vao = 0;
    buffer = NULL;
    constructed = false;
}

VAO::~VAO()
{
   if(constructed)
   glDeleteVertexArrays(1,&vao);

   if(buffer)
    delete []buffer;
}

void VAO::Construct(int buff_n)
{
	buffer = new GLuint[buff_n];

	glGenVertexArrays(1,&vao);

	bind();

	glGenBuffers(buff_n,buffer);

	constructed = true;
}

void VAO::DeleteBuffer(int buff_n)
{
	glDeleteBuffers(1,&buffer[buff_n]);
}

void VAO::GenBuffer(int buff_n)
{
   glGenBuffers(1,&buffer[buff_n]);
}

void VAO::ResetBuffer(int buff_n)
{
	DeleteBuffer(buff_n);
    GenBuffer(buff_n);
}

void VAO::bind()
{
	glBindVertexArray(vao);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::BufferData(int buff,GLenum target,GLsizeiptr size,GLvoid *data,GLenum mode)
{
	glBindBuffer(target,buffer[buff]);
	glBufferData(target,size,data,mode);
}

void VAO::VertexAttribute(int location,int size,GLenum type,GLboolean normalized,GLsizei stride,GLvoid *pointer)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location,size,type,normalized,stride,pointer);
}



void VAO::DrawArrays(GLenum mode,GLint first,GLsizei count,void *indices)
{
	bind();
	if(!indices)
	  glDrawArrays(mode,first,count);
	else
	  glDrawElements(mode,count,GL_FLOAT,indices);
	unbind();
}
