#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "vec.h"
#include <list>

void SetKeyState(SDL_Scancode scancode, Uint8 type);
Uint32 GetKeyState(SDL_Scancode scancode);

vec2_t rotate(float angle);
vec2_t GetRelativeMouse();

class CAverage
{
public:
	float average = 0.0F;
	float set_average(float frame, size_t count = 5);
	void clear() { frames.clear(); }

private:
	std::list<float> frames;
};

#endif // ENGINE_H