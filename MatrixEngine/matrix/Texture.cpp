#include "Texture.h"

Texture::Texture()
{
	texture_id = 0;
	texture_file = "none";
	glTexture = false;
	texture_unit = 0;

}

Texture::Texture(string file)
{
	load_from_file(file);
}

Texture::~Texture()
{
    if(texture_id)
	{
	    cout<<"destroying texture.."<<endl;
		glDeleteTextures(1,&texture_id);
	}
}

void Texture::load_from_file(string file)
{
	WriteOnStream("Loading texture "+file,log_stream);

	SDL_Surface *texture = NULL;
	int channels = 0;
	GLenum format;

	texture = IMG_Load(file.c_str());

	if(!texture)
	{
		WriteOnStream("Could not load texture: " + file, error_stream);
		return;
	}

	channels = texture->format->BytesPerPixel;

	if(channels == 4)
	{
		if(texture->format->Rmask == 0x000000ff)
		{
			format = GL_RGBA;
		}
		else
		{
			format = GL_BGRA;
		}
	}
	else if(channels == 3)
	{
        if(texture->format->Rmask == 0x000000ff)
		{
			format = GL_RGB;
		}
		else
		{
			format = GL_BGR;
		}
	}
	else
	{
		WriteOnStream("Texture " + file + " isn't true color. This will break", error_stream);
	}

	glGenTextures(1,&texture_id);
	glBindTexture(GL_TEXTURE_2D,texture_id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,channels,texture->w,texture->h,0,format,GL_UNSIGNED_BYTE,texture->pixels);

	SDL_FreeSurface(texture);

    texture_file = file;
	WriteOnStream("Loaded", log_stream);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D,texture_id);
}

void Texture::bind_unit(int unit)
{
	glActiveTexture(GL_TEXTURE0+unit);
	bind();
	texture_unit = unit;
	glTexture = true;
}

void Texture::unbind()
{
	if(glTexture)
	{
		glActiveTexture(GL_TEXTURE0+texture_unit);
		glTexture = false;
	}

	glBindTexture(GL_TEXTURE_2D,0);
}

/** Texture Cube */

TextureCube::TextureCube()
{
	texture_id = 0;
	for(int i = 0;i < 6;i++)
	{
		texture_file[i] = " ";
	}

	shader = NULL;
	shader_vert = shader_frag = NULL;
}

TextureCube::TextureCube(string *files)
{
	load_from_file(files);

}

TextureCube::~TextureCube()
{
	if(texture_id)
	{
			glDeleteTextures(1,&texture_id);
	}

	if(shader)
	{
	    shader->detach_shader(shader_vert);
	    shader->detach_shader(shader_frag);

	    delete shader_vert;
	    delete shader_frag;
	    delete shader;
	}
}


void TextureCube::load_from_file(string *files)
{
    shader = new ShaderProgram();
	shader_vert = new ShaderSource();
	shader_frag = new ShaderSource();

	shader_vert->load_from_file(GL_VERTEX_SHADER,"data/shader/cubemap.vert");
	shader_frag->load_from_file(GL_FRAGMENT_SHADER,"data/shader/cubemap.frag");

	shader->attach_shader(shader_vert);
	shader->attach_shader(shader_frag);
	shader->compile();

	WriteOnStream("In TextureCube: Loading Cubemap..", log_stream);
	int nOfColors = 0;
    SDL_Surface *image[6];
    GLenum texture_format;

	for(int i = 0;i < 6;i++)
	{
	  WriteOnStream("In TextureCube::load_from_file: loading " + files[i], log_stream);
	  texture_file[i] = files[i];
	  image[i] = NULL;
	  image[i] = IMG_Load(files[i].c_str());

      if(!image[i])
	  {
		  WriteOnStream("\tCANNOT LOAD " + files[i] + " texture! ", error_stream);
		  return;
	  }
	}


	 if(image[0])
	 {
		nOfColors = image[0]->format->BytesPerPixel;
		if(nOfColors == 4)
		{
			if( image[0]->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		}
		else if(nOfColors == 3)
		{
			if (image[0]->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		}
		else
		{
			WriteOnStream("TextureCube isn't true color. This will break", error_stream);
			return;
		}
	 }



	glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP,texture_id);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,nOfColors,image[0]->w,image[0]->h,0,texture_format,GL_UNSIGNED_BYTE,image[0]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,nOfColors,image[1]->w,image[1]->h,0,texture_format,GL_UNSIGNED_BYTE,image[1]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,nOfColors,image[2]->w,image[2]->h,0,texture_format,GL_UNSIGNED_BYTE,image[2]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,nOfColors,image[3]->w,image[3]->h,0,texture_format,GL_UNSIGNED_BYTE,image[3]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,nOfColors,image[4]->w,image[4]->h,0,texture_format,GL_UNSIGNED_BYTE,image[4]->pixels);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,nOfColors,image[5]->w,image[5]->h,0,texture_format,GL_UNSIGNED_BYTE,image[5]->pixels);

	WriteOnStream("Loaded", log_stream);

}

void TextureCube::bind()
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP,texture_id);

	mat4 glModelMatrix = mat4(1);
	glModelMatrix = glm::translate(glModelMatrix,vec3(-_pCurrentCamera->GetPosition().x,
						    -_pCurrentCamera->GetPosition().y,
							-_pCurrentCamera->GetPosition().z));

	shader->sendUniformMatrix4fv(shader->getUniformLocation("projMat"),1,GL_FALSE,GLXSDLRenderPipeline::glProjectionMatrix);
	shader->sendUniformMatrix4fv(shader->getUniformLocation("viewMat"),1,GL_FALSE,GLXSDLRenderPipeline::glViewMatrix);
	shader->sendUniformMatrix4fv(shader->getUniformLocation("modMat"),1,GL_FALSE,glModelMatrix);
	shader->sendUniform1i(shader->getUniformLocation("cubemap"),0);

	shader->bind();

	Graphics::_pCurrentTextureCube = this;
}

void TextureCube::unbind()
{
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);

	shader->unbind();
}

void TextureCube::bind_unit(int unit)
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0+unit);
	bind();
}


void TextureCube::unbind_unit(int unit)
{
	glDisable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0+unit);
	unbind();
}

