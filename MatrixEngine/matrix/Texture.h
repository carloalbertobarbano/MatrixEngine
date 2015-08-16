#ifndef GL3_TEXTURE_H
#define GL3_TEXTURE_H

#include "matrix_engine_internal.h"
#include "GLXSDLCamera.h"
#include "Shader.h"


using namespace MatrixEngine;
using namespace MatrixEngine::Graphics;
using namespace MatrixEngine::IOStream;

class Graphics::Texture
{
  public :
	  Texture();
	  Texture(string file);
	  ~Texture();

	  void load_from_file(string file);

	  void bind();
	  void bind_unit(int unit);
	  void unbind();

	  operator GLuint() { return texture_id; }
	  GLuint get_texture(){ return texture_id; }

      string getName(){ return texture_file; }

      static void ActiveAndBindUnit(int unit,GLuint texture)
      {
          glActiveTexture(GL_TEXTURE0+unit);
          glBindTexture(GL_TEXTURE_2D,texture);
      }

  protected :
	  GLuint texture_id;
	  string texture_file;

	  bool glTexture;
	  int texture_unit;
};


class Graphics::TextureCube
{
  public :
	TextureCube();
	TextureCube(string *files);
	~TextureCube();

	void load_from_file(string *files);
	void bind();
	void unbind();

	void bind_unit(int unit);
	void unbind_unit(int unit);

	operator GLuint() { return texture_id; }
	GLuint get_texture(){ return texture_id; }

  protected :
    GLuint texture_id;
	string texture_file[6];

	ShaderProgram *shader;
	ShaderSource *shader_vert,*shader_frag;
};

#endif
