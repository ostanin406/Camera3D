#pragma once

#ifndef VEC_H
#define VEC_H

#include <cmath>

struct vec2_t
{
	float x, y;

	vec2_t(float all = 0.0F) { x = y = all; }
	vec2_t(float x, float y) : x(x), y(y) {}

	vec2_t operator * (const float a) { return vec2_t(x * a, y * a); }
	vec2_t operator - (const float a) { return vec2_t(x - a, y - a); }
	vec2_t operator + (const float a) { return vec2_t(x + a, y + a); }
	vec2_t operator / (const float a) { return vec2_t(x / a, y / a); }

	vec2_t operator * (const vec2_t& a) { return vec2_t(x * a.x, y * a.y); }
	vec2_t operator - (const vec2_t& a) { return vec2_t(x - a.x, y - a.y); }
	vec2_t operator + (const vec2_t& a) { return vec2_t(x + a.x, y + a.y); }
	vec2_t operator / (const vec2_t& a) { return vec2_t(x / a.x, y / a.y); }

	vec2_t& operator *= (const float a) { x *= a; y *= a; return *this; }
	vec2_t& operator -= (const float a) { x -= a; y -= a; return *this; }
	vec2_t& operator += (const float a) { x += a; y += a; return *this; }
	vec2_t& operator /= (const float a) { x /= a; y /= a; return *this; }

	vec2_t& operator *= (const vec2_t& a) { x *= a.x; y *= a.y; return *this; }
	vec2_t& operator -= (const vec2_t& a) { x -= a.x; y -= a.y; return *this; }
	vec2_t& operator += (const vec2_t& a) { x += a.x; y += a.y; return *this; }
	vec2_t& operator /= (const vec2_t& a) { x /= a.x; y /= a.y; return *this; }

	vec2_t& operator = (const vec2_t& a) { x = a.x; y = a.y; return *this; }
	vec2_t& operator = (const float a) { x = a; y = a; return *this; }

	friend vec2_t operator * (const float a, const vec2_t& b) { return vec2_t(a * b.x, a * b.y); }
	friend vec2_t operator - (const float a, const vec2_t& b) { return vec2_t(a - b.x, a - b.y); }
	friend vec2_t operator + (const float a, const vec2_t& b) { return vec2_t(a + b.x, a + b.y); }
	friend vec2_t operator / (const float a, const vec2_t& b) { return vec2_t(a / b.x, a / b.y); }

	vec2_t min(vec2_t a)
	{
		return vec2_t((x < a.x ? x : a.x), (y < a.y ? y : a.y));
	}

	vec2_t max(vec2_t a)
	{
		return vec2_t((x > a.x ? x : a.x), (y > a.y ? y : a.y));
	}

	vec2_t clamp(vec2_t min, vec2_t max)
	{
		return vec2_t((x > max.x ? max.x : (x < min.x ? min.x : x)), (y > max.y ? max.y : (y < min.y ? min.y : y)));
	}

	float length()
	{
		return sqrtf(x * x + y * y);
	}

	vec2_t normalize()
	{
		float a = sqrtf(x * x + y * y) + 1.0F;
		return vec2_t(x / a, y / a);
	}
};

struct vec3_t
{
	float x, y, z;

	vec3_t(float all = 0.0F) { x = y = z = all; }
	vec3_t(float x, float y, float z) : x(x), y(y), z(z) {}

	vec3_t operator * (const float a) { return vec3_t(x * a, y * a, z * a); }
	vec3_t operator - (const float a) { return vec3_t(x - a, y - a, z - a); }
	vec3_t operator + (const float a) { return vec3_t(x + a, y + a, z + a); }
	vec3_t operator / (const float a) { return vec3_t(x / a, y / a, z / a); }

	vec3_t operator * (const vec3_t& a) { return vec3_t(x * a.x, y * a.y, z * a.z); }
	vec3_t operator - (const vec3_t& a) { return vec3_t(x - a.x, y - a.y, z - a.z); }
	vec3_t operator + (const vec3_t& a) { return vec3_t(x + a.x, y + a.y, z + a.z); }
	vec3_t operator / (const vec3_t& a) { return vec3_t(x / a.x, y / a.y, z / a.z); }

	vec3_t& operator *= (const float a) { x *= a; y *= a; z *= a; return *this; }
	vec3_t& operator -= (const float a) { x -= a; y -= a; z -= a; return *this; }
	vec3_t& operator += (const float a) { x += a; y += a; z += a; return *this; }
	vec3_t& operator /= (const float a) { x /= a; y /= a; z /= a; return *this; }

	vec3_t& operator *= (const vec3_t& a) { x *= a.x; y *= a.y; z *= a.z; return *this; }
	vec3_t& operator -= (const vec3_t& a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
	vec3_t& operator += (const vec3_t& a) { x += a.x; y += a.y; z += a.z; return *this; }
	vec3_t& operator /= (const vec3_t& a) { x /= a.x; y /= a.y; z /= a.z; return *this; }

	vec3_t& operator = (const vec3_t& a) { x = a.x; y = a.y; z = a.z; return *this; }
	vec3_t& operator = (const float a) { x = a; y = a; z = a; return *this; }

	friend vec3_t operator * (const float a, const vec3_t& b) { return vec3_t(a * b.x, a * b.y, a * b.z); }
	friend vec3_t operator - (const float a, const vec3_t& b) { return vec3_t(a - b.x, a - b.y, a - b.z); }
	friend vec3_t operator + (const float a, const vec3_t& b) { return vec3_t(a + b.x, a + b.y, a + b.z); }
	friend vec3_t operator / (const float a, const vec3_t& b) { return vec3_t(a / b.x, a / b.y, a / b.z); }

	vec3_t cross(vec3_t a)
	{
		return vec3_t((y * a.z - z * a.y), (z * a.x - x * a.z), (x * a.y - y * a.x));
	}

	vec3_t min(vec3_t a)
	{
		return vec3_t((x < a.x ? x : a.x), (y < a.y ? y : a.y), (z < a.z ? z : a.z));
	}

	vec3_t max(vec3_t a)
	{
		return vec3_t((x > a.x ? x : a.x), (y > a.y ? y : a.y), (z > a.z ? z : a.z));
	}

	vec3_t clamp(vec3_t min, vec3_t max)
	{
		return vec3_t((x > max.x ? max.x : (x < min.x ? min.x : x)), (y > max.y ? max.y : (y < min.y ? min.y : y)), (z > max.z ? max.z : (z < min.z ? min.z : z)));
	}

	float length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	vec3_t normalize()
	{
		float a = sqrtf(x * x + y * y + z * z) + 1.0F;
		return vec3_t(x / a, y / a, z / a);
	}
};

#endif // VEC_H