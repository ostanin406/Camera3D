#pragma once

#ifndef STR_H
#define STR_H

#include <cstdio>
#include <cmath>
#include <cstring>

inline char* strnum(float num)
{
	char* c = new char[32];
	sprintf(c, num - truncf((float)num) != 0 ? "%f" : "%i", num);
	return c;
}

inline char* append(const char* a, const char* b)
{
	char* c = new char[strlen(a) + strlen(b)];
	strcpy(c, a); strcat(c, b); return c;
}

struct str_t
{
	char* cstr;

	str_t() { cstr = NULL; }
	str_t(const char* string) { cstr = new char[strlen(string)]; strcpy(cstr, string); }

	str_t operator + (const char* string) { return str_t(append(cstr, string)); }
	str_t operator + (const str_t& str) { return str_t(append(cstr, str.cstr)); }
	str_t operator + (const float a) { return str_t(append(cstr, strnum(a))); }
	str_t operator + (const int a) { return str_t(append(cstr, strnum((float)a))); }

	str_t& operator += (const char* string) { cstr = append(cstr, string); return *this; }
	str_t& operator += (const str_t& str) { cstr = append(cstr, str.cstr); return *this; }
	str_t& operator += (const float a) { cstr = append(cstr, strnum(a)); return *this; }
	str_t& operator += (const int a) { cstr = append(cstr, strnum((float)a)); return *this; }

	str_t& operator = (const char* string) { cstr = new char[strlen(string)]; strcpy(cstr, string); return *this; }
	str_t& operator = (const str_t& str) { str_t(str.cstr); return *this; }
	str_t& operator = (const float a) { cstr = strnum(a); return *this; }
	str_t& operator = (const int a) { cstr = strnum((float)a); return *this; }

	friend str_t operator + (const char* string, const str_t& str) { return str_t(append(string, str.cstr)); }
	friend str_t operator + (const float a, const str_t& str) { return str_t(append(strnum(a), str.cstr)); }
	friend str_t operator + (const int a, const str_t& str) { return str_t(append(strnum((float)a), str.cstr)); }
};

#endif // STR_H