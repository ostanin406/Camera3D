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
};

vec2_t rotate(float angle);
float length(vec2_t a);
vec2_t normalize(vec2_t a);
vec2_t clamp(vec2_t a, vec2_t min, vec2_t max);
vec2_t max(vec2_t a, vec2_t b);
vec2_t min(vec2_t a, vec2_t b);

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
};

float length(vec3_t a);
vec3_t normalize(vec3_t a);
vec3_t clamp(vec3_t a, vec3_t min, vec3_t max);
vec3_t max(vec3_t a, vec3_t b);
vec3_t min(vec3_t a, vec3_t b);
vec3_t cross(vec3_t a, vec3_t b);

#endif // VEC_H