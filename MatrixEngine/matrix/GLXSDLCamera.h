#ifndef GLXSDL_CAMERA_H
#define GLXSDL_CAMERA_H

#include "matrix_engine_internal.h"
#include "GLXSDLRenderPipeline.h"


using namespace MatrixEngine;

class MatrixEngine::GLXSDLCamera
{
public:
	GLXSDLCamera();

	void SetPosition(vec3 pos);
	void SetPitch(float p);
	void SetYaw(float y);

	vec3  GetPosition();
	float GetPitch();
	float GetYaw();

	void MoveStrafe(float distance, float direction);
	void MoveUp(float dist, float direction);

	void ApplyTransform();

	mat4 getViewMatrixNotRotated(){ return glViewMatrixNotRotated; }

protected:
	vec3 position;
	float pitch, yaw;

	void Lock();

	mat4 glViewMatrixNotRotated;
};

#endif