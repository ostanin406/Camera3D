#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

bool LoadTexture(GLuint& texture, const char* texname, bool clamp = false);
bool LoadSkybox(GLuint skybox[6], const char* skyname);

#endif // TEXTURE_H