#ifndef _LOADTEXTURE_H  
#define _LOADTEXTURE_H  

#include "Main.h"


class LoadTexture
{
public:
    static GLuint LoadTextureImageFile(const char* filename, int width, int height);

};

#endif