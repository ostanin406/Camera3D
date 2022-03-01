#include "vec.h"
#include <SDL.h>

vec2_t rotate(float angle)
{
	float rad = angle * (float)M_PI / 180.0F;
	return vec2_t(sinf(rad), cosf(rad));
}

float length(vec2_t a)
{
	return sqrtf(a.x * a.x + a.y * a.y);
}

vec2_t normalize(vec2_t a)
{
	float len = length(a) + 1.0F;
	return vec2_t(a.x / len, a.y / len);
}

vec2_t clamp(vec2_t a, vec2_t min, vec2_t max)
{
	return vec2_t((a.x > max.x ? max.x : (a.x < min.x ? min.x : a.x)),
		(a.y > max.y ? max.y : (a.y < min.y ? min.y : a.y)));
}

vec2_t max(vec2_t a, vec2_t b)
{
	return vec2_t((b.x > a.x ? b.x : a.x),
		(b.y > a.y ? b.y : a.y));
}

vec2_t min(vec2_t a, vec2_t b)
{
	return vec2_t((b.x < a.x ? b.x : a.x),
		(b.y < a.y ? b.y : a.y));
}

float length(vec3_t a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

vec3_t normalize(vec3_t a)
{
	float len = length(a) + 1.0F;
	return vec3_t(a.x / len, a.y / len, a.z / len);
}

vec3_t clamp(vec3_t a, vec3_t min, vec3_t max)
{
	return vec3_t((a.x > max.x ? max.x : (a.x < min.x ? min.x : a.x)),
		(a.y > max.y ? max.y : (a.y < min.y ? min.y : a.y)),
		(a.z > max.z ? max.z : (a.z < min.z ? min.z : a.z)));
}

vec3_t max(vec3_t a, vec3_t b)
{
	return vec3_t((b.x > a.x ? b.x : a.x),
		(b.y > a.y ? b.y : a.y),
		(b.z > a.z ? b.z : a.z));
}

vec3_t min(vec3_t a, vec3_t b)
{
	return vec3_t((b.x < a.x ? b.x : a.x),
		(b.y < a.y ? b.y : a.y),
		(b.z < a.z ? b.z : a.z));
}

vec3_t cross(vec3_t a, vec3_t b)
{
	return vec3_t((b.y * a.z - b.z * a.y),
		(b.z * a.x - b.x * a.z),
		(b.x * a.y - b.y * a.x));
}