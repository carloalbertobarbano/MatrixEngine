#include "Mouse.h"

Mouse::Mouse()
{
	if (_pCurrentDevice){
		mouse_pos = vec2(_pCurrentDevice->GetResolution().x,_pCurrentDevice->GetResolution().y) / vec2(2.0);
	    
	} else
		mouse_pos = vec2(0.0);

	sensibility = 0.7;
}

vec2 Mouse::GetMousePos()
{
	int x = 0, y = 0;

	SDL_GetMouseState(&x, &y);

	mouse_pos = vec2(x, y);

	return mouse_pos;
}

void Mouse::SetSensibility(float s)
{
	sensibility = s;
}

float Mouse::GetSensibility()
{
	return sensibility;
}

void Mouse::UpdateCamera(GLXSDLCamera *camera)
{
	vec2 middle = vec2(_pCurrentDevice->GetResolution().x, _pCurrentDevice->GetResolution().y) / vec2(2.0);

	GetMousePos();

	if (camera)
	{
		SDL_ShowCursor(SDL_DISABLE);
		float yaw = camera->GetYaw() + sensibility * (mouse_pos.x - middle.x);
		float pitch = camera->GetPitch() + sensibility * (mouse_pos.y - middle.y);

		camera->SetYaw(yaw);
		camera->SetPitch(pitch);

		SDL_WarpMouse(middle.x, middle.y);
	}
}