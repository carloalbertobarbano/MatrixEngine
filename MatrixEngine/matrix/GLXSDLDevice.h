#ifndef GL_DEVICE_H
#define GL_DEVICE_H

#include "matrix_engine_internal.h"

using namespace MatrixEngine;

class MatrixEngine::GLXSDLDevice {
	public :
		GLXSDLDevice();
		GLXSDLDevice(Uint32 flags, glm::vec3 resolution, bool fullscreen = false);

		bool Construct(Uint32 flags, glm::vec3 resolution, bool fullscreen = false);
		bool SetResolution(glm::vec3 resolution, bool fullscreen = false);

		void SetCaption(string caption, string icon = "");

		glm::vec3 inline GetResolution(){ return resolution; };
	protected :
		glm::vec3 resolution;
		
		SDL_Surface *screen;

		void InitGL();

};

#endif