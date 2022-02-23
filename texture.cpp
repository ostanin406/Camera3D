#include <cstdio>
#include <GL/glew.h>
#include <FreeImage.h>
#include <SDL.h>
#include "texture.h"
#include <string>

#pragma warning(push)
#pragma warning(disable:26812)
bool LoadTexture(GLuint& texture, const char* texname, bool clamp)
{
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(texname);
    if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(texname);

    if ((fif == FIF_UNKNOWN) || !FreeImage_FIFSupportsReading(fif))
    {
        printf("[FreeImage] File type error: %s\n", texname);
        return false;
    }

    FIBITMAP* dib = FreeImage_Load(fif, texname);
    if (!dib)
    {
        printf("[FreeImage] Error load file: %s\n", texname);
        return false;
    }

    Uint32 bpp = FreeImage_GetBPP(dib);

    if (bpp != 32 && bpp != 24)
    {
        dib = FreeImage_ConvertTo24Bits(dib);
        if (!dib)
        {
            printf("[FreeImage] Error convert file: %s\n", texname);
            return false;
        }
        bpp = 24;
    }

    BYTE* bits = FreeImage_GetBits(dib);
    Uint32 width = FreeImage_GetWidth(dib);
    Uint32 height = FreeImage_GetHeight(dib);

    if ((bits == 0) || (width == 0) || (height == 0))
    {
        printf("[FreeImage] Error read file: %s\n", texname);
        return false;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);

    if (gluBuild2DMipmaps(GL_TEXTURE_2D, bpp / 8, width, height, bpp == 32 ? GL_BGRA : GL_BGR, GL_UNSIGNED_BYTE, bits) != 0)
    {
        printf("[FreeImage] Error \"gluBuild2DMipmaps\"\n");
        return false;
    }

    FreeImage_Unload(dib);
    return true;
}
#pragma warning(pop)

const char* gSkybox[] = { "_rt", "_lf","_bk" ,"_ft","_dn" ,"_up" };

bool LoadSkybox(GLuint skybox[6], const char* skyname)
{
    for (int i = 0; i < 6; i++)
    {
        if (!LoadTexture(skybox[i], (std::string(skyname) + gSkybox[i]).c_str(), true))
        {
            printf("[SkyBox] Error load sky texture: %s\n", skyname);
            return false;
        }
    }
    return true;
}