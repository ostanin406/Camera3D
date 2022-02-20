#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include "vec.h"
#include "str.h"
#include <list>

void SetKeyState(SDL_Scancode scancode, Uint8 type);
Uint32 GetKeyState(SDL_Scancode scancode);

vec2_t rotate(float angle);
vec2_t GetRelativeMouse();

struct cvar_t
{
private:
	str_t name, str;
	float value;

public:
	cvar_t(const char* name, const char* string) : name(name), str(string) { value = (float)atof(str.cstr); }
	cvar_t(const char* name, float value) : name(name), value(value) { str = value; }
	cvar_t(const char* name, int value) : name(name), value((float)value) { str = value; }

	void set_string(const char* string)
	{
		str = string;
		value = (float)atof(string);
	}

	void set_float(const float num)
	{
		str = num;
		value = num;
	}

	void set_int(const int num)
	{
		str = num;
		value = (float)num;
	}

	char* get_string()
	{
		return str.cstr;
	}

	float get_float()
	{
		return value;
	}

	int get_int()
	{
		return (int)roundf(value);
	}
};

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