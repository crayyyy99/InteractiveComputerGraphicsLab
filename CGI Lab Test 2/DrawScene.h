#ifndef _DRAWSCENE_H  
#define _DRAWSCENE_H  

#include "Main.h"

class DrawScene
{
public:

    void SingleTexture(GLuint textureSet[6], const char* file_name, int w, int h);
    void FreeCreatedTextures();

    void DisplayTexturedScene_Roof();
    void DisplayTexturedScene_Stage();
    void DisplayTexturedScene_Machine();
    void DisplayTexturedScene_Shop();

};


#endif  