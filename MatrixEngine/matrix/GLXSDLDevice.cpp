#include "GLXSDLDevice.h"

GLXSDLDevice::GLXSDLDevice()
{

}

GLXSDLDevice::GLXSDLDevice(Uint32 flags, glm::vec3 resolution, bool fullscreen)
{
	this->Construct(flags, resolution, fullscreen);
}

bool GLXSDLDevice::Construct(Uint32 flags, glm::vec3 res, bool fullscreen)
{	
	SDL_Init(flags);

	//Set resolution
	if (!this->SetResolution(res, fullscreen)){
		return false;
	}

	this->resolution = res;
	InitGL();

	_pCurrentDevice = this;

	return true;
}

bool GLXSDLDevice::SetResolution(glm::vec3 res, bool fullscreen)
{
	screen = SDL_SetVideoMode(res.x, res.y, res.z, SDL_SWSURFACE | SDL_GL_DOUBLEBUFFER | (fullscreen ? SDL_OPENGL | SDL_FULLSCREEN : SDL_OPENGL));

	if (!screen)
	{
		IOStream::WriteOnStream("Cannot create screen surface",IOStream::error_stream);
		return false;
	} 

	return true;
}

void GLXSDLDevice::SetCaption(string caption, string icon)
{
	SDL_WM_SetCaption(caption.c_str(), icon.c_str());
}


void GLXSDLDevice::InitGL()
{
	stringstream s;
	s << "OpenGL Version: " << atof((const char*)glGetString(GL_VERSION));

	IOStream::WriteOnStream(s.str(), IOStream::log_stream);

	glewInit();
}