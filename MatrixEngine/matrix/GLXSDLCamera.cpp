#include "GLXSDLCamera.h"

GLXSDLCamera::GLXSDLCamera()
{
	pitch = 0.0;
	yaw = 0.0;

	position = vec3(0.0);
}

void GLXSDLCamera::SetPosition(vec3 pos)
{
	position = pos;
}

void GLXSDLCamera::SetPitch(float p)
{
	pitch = p;
}

void GLXSDLCamera::SetYaw(float y)
{
	yaw = y;
}

vec3 GLXSDLCamera::GetPosition()
{
	return position;
}

float GLXSDLCamera::GetPitch()
{
	return pitch;
}

float GLXSDLCamera::GetYaw()
{
	return yaw;
}

void GLXSDLCamera::MoveStrafe(float dist, float dir)
{
	float rad = (yaw + dir) * PI / 180.0;

	position.x -= sin(rad)*dist;
	position.z += cos(rad)*dist;
}

void GLXSDLCamera::MoveUp(float dist, float dir)
{
	float rad = (pitch + dir) * PI / 180.0;

	position.y += sin(rad)*dist;
}

void GLXSDLCamera::ApplyTransform()
{
	Lock();
	GLXSDLRenderPipeline::glViewMatrix = glm::rotate(GLXSDLRenderPipeline::glViewMatrix, pitch, vec3(1.0, 0.0, 0.0));
	GLXSDLRenderPipeline::glViewMatrix = glm::rotate(GLXSDLRenderPipeline::glViewMatrix, yaw, vec3(0.0, 1.0, 0.0));
	GLXSDLRenderPipeline::glViewMatrix = glm::translate(GLXSDLRenderPipeline::glViewMatrix, position);
	
	glViewMatrixNotRotated = mat4(1); // LoadIdentity();
	glViewMatrixNotRotated = glm::translate(glViewMatrixNotRotated, position);

	MatrixEngine::_pCurrentCamera = this;
}

void GLXSDLCamera::Lock()
{
	if (pitch > 90.0)pitch = 90.0;
	if (pitch < -90.0)pitch = -90.0;

	if (yaw < 0.0)yaw += 360.0;
	if (yaw > 360)yaw -= 360.0;
}
