#include "engine.h"

Uint32 KeyState[SDL_NUM_SCANCODES];

#pragma warning(push)
#pragma warning(disable:26812)
void SetKeyState(SDL_Scancode scancode, Uint8 type)
{
	KeyState[scancode] = type ? 1 : 0;
}

Uint32 GetKeyState(SDL_Scancode scancode)
{
	Uint32 key = KeyState[scancode];
	if (key >= 1) KeyState[scancode]++;
	return key;
}
#pragma warning(pop)

vec2_t GetRelativeMouse()
{
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	return vec2_t((float)y, (float)x); // invert
}

float CAverage::set_average(float frame, size_t count)
{
	size_t size = frames.size();
	if (size >= count) frames.pop_front();
	frames.push_back(frame);

	if (size > 1)
	{
		float sum = 0.0F;
		for (float& i : frames) sum += i;
		return average = sum / size;
	}
	return average = frame;
}