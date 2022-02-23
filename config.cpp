#include "config.h"
#include <map>

std::map<std::string, float> gFCvar;
std::map<std::string, std::string> gSCvar;

float* register_cvar(const char* name, float value)
{
	std::map<std::string, float>::const_iterator iter;

	iter = gFCvar.find(name);
	if (iter == gFCvar.end()) gFCvar[name] = value;
	else printf("[Warning] %s cvar is already there\n", name);

	return &gFCvar[name];
}

std::string* register_cvar(const char* name, std::string value)
{
	std::map<std::string, std::string>::const_iterator iter;

	iter = gSCvar.find(name);
	if (iter == gSCvar.end()) gSCvar[name] = value;
	else printf("[Warning] %s cvar is already there\n", name);

	return &gSCvar[name];
}

float get_fcvar(const char* name)
{
	std::map<std::string, float>::const_iterator iter;

	iter = gFCvar.find(name);
	if (iter == gFCvar.end())
		printf("[Error] cvar %s does not exist\n", name);

	return (*iter).second;
}

std::string get_scvar(const char* name)
{
	std::map<std::string, std::string>::const_iterator iter;

	iter = gSCvar.find(name);
	if (iter == gSCvar.end())
		printf("[Error] cvar %s does not exist\n", name);

	return (*iter).second;
}

void set_fcvar(const char* name, float value)
{
	std::map<std::string, float>::const_iterator iter;

	iter = gFCvar.find(name);
	if (iter != gFCvar.end()) gFCvar[name] = value;
	else printf("[Error] cvar %s does not exist\n", name);
}

void set_scvar(const char* name, std::string value)
{
	std::map<std::string, std::string>::const_iterator iter;

	iter = gSCvar.find(name);
	if (iter != gSCvar.end()) gSCvar[name] = value;
	else printf("[Error] cvar %s does not exist\n", name);
}