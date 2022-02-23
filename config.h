#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

float* register_cvar(const char* name, float value);
std::string* register_cvar(const char* name, std::string value);
float get_fcvar(const char* name);
std::string get_scvar(const char* name);
void set_fcvar(const char* name, float value);
void set_scvar(const char* name, std::string value);

#endif // CONFIG_H