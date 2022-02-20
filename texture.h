#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

Uint32 LoadTexture(const char* texname);
Uint32* LoadSkybox(const char* skyname);

#endif // TEXTURE_H