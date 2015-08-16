#ifndef GL3_KEYBOARD_H
#define GL3_KEYBOARD_H

#include "matrix_engine_internal.h"

using namespace MatrixEngine;
using namespace MatrixEngine::Devices;

class Devices::Keyboard
{
public:
	Keyboard();

	bool key[SDLK_LAST];
};

#endif