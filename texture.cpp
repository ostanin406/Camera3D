#include <cstdio>
#include <GL/glew.h>
#include <FreeImage.h>
#include "texture.h"
#include "str.h"

#pragma warning(push)
#pragma warning(disable:26812)
Uint32 LoadTexture(const char* texname)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(texname);
    if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(texname);

    if ((fif == FIF_UNKNOWN) || !FreeImage_FIFSupportsReading(fif))
        return printf("[FreeImage] File type error: %s\n", texname);

    FIBITMAP* dib = FreeImage_Load(fif, texname);
    if (!dib) return printf("[FreeImage] Error load file: %s\n", texname);

    Uint32 bpp = FreeImage_GetBPP(dib);

    if (bpp != 32 && bpp != 24)
    {
        dib = FreeImage_ConvertTo24Bits(dib);
        if (!dib) return printf("[FreeImage] Error convert file: %s\n", texname);
        bpp = 24;
    }

    BYTE* bits = FreeImage_GetBits(dib);
    Uint32 width = FreeImage_GetWidth(dib);
    Uint32 height = FreeImage_GetHeight(dib);

    if ((bits == 0) || (width == 0) || (height == 0))
        return printf("[FreeImage] Error read file: %s\n", texname);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (gluBuild2DMipmaps(GL_TEXTURE_2D, bpp / 8, width, height, bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, bits) != 0)
        return printf("[FreeImage] Error \"gluBuild2DMipmaps\"\n");

    FreeImage_Unload(dib);
    return texture;
}
#pragma warning(pop)

const char* gSkybox[] = { "_rt", "_lf","_bk" ,"_ft","_dn" ,"_up" };

Uint32* LoadSkybox(const char* skyname)
{
    Uint32* skybox = new Uint32[6];
    for (int i = 0; i < 6; i++)
        skybox[i] = LoadTexture(append(skyname, gSkybox[i]));
    return skybox;
}