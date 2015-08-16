#ifndef GL3_MOUSE_H
#define GL3_MOUSE_H

#include "matrix_engine_internal.h"
#include "GLXSDLCamera.h"

using namespace MatrixEngine;
using namespace MatrixEngine::Devices;


class Devices::Mouse
{
public:
	Mouse();

	vec2 GetMousePos();

	void SetSensibility(float s);
	float GetSensibility();
	void UpdateCamera(GLXSDLCamera *camera);

protected:
	vec2 mouse_pos;
	float sensibility;
};

#endif