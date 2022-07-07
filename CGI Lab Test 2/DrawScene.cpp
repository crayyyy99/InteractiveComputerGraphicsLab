#include "DrawScene.h"
#include "LoadTexture.h"  
#include "DrawPrimitives.h"
  
GLuint floor_texture[6];
GLuint roof_texture[6];
GLuint logo_texture[6];
GLuint stage_texture[6];
GLuint carBlock_texture[6];
GLuint carBlockSide_texture[6];
GLuint machineFrame2_texture[6];
GLuint machine_texture[6];
GLuint warningSignR_texture[6];
GLuint warningSignL_texture[6];
GLuint rubbishBin_texture[6];
GLuint advSign_texture[6];
GLuint shop_texture[6];

DrawPrimitives dp;

void DrawScene::SingleTexture(GLuint textureSet[6], const char* file_name, int w, int h)
{
    textureSet[5] = LoadTexture::LoadTextureImageFile(file_name, w, h);
    textureSet[0] = textureSet[1] = textureSet[2] = textureSet[3] = textureSet[4] = textureSet[5];
};

void DrawScene::FreeCreatedTextures()
{
	for (int i = 0; i < 6; i++)
	{
		glDeleteTextures(1, &floor_texture[i]);
		glDeleteTextures(1, &roof_texture[i]);
        glDeleteTextures(1, &stage_texture[i]);
        glDeleteTextures(1, &carBlock_texture[i]);
        glDeleteTextures(1, &carBlockSide_texture[i]);
        glDeleteTextures(1, &machineFrame2_texture[i]);
        glDeleteTextures(1, &machine_texture[i]);
        glDeleteTextures(1, &rubbishBin_texture[i]);
        glDeleteTextures(1, &advSign_texture[i]);
        glDeleteTextures(1, &shop_texture[i]);

	}
    glDeleteTextures(1, &logo_texture[1]);
    glDeleteTextures(1, &logo_texture[3]);
    glDeleteTextures(1, &warningSignR_texture[3]);
    glDeleteTextures(1, &warningSignL_texture[5]);
}

//w h l dx dy dz

//textures[] -> 0-Back 1-front 2-bottom 3-right 4-top 5-left

void DrawScene::DisplayTexturedScene_Roof()
{
    //floor
    glColor3ub(134, 136, 138); //medium grey
    dp.DrawCuboid(7.1, 0.02, 4.57, 0, -2.53, -0.51);
    dp.DrawCuboid(4.6, 0.02, 4.2, 0, -2.53, -8.12);
    glColor3ub(202, 204, 206); //light grey
    SingleTexture(floor_texture, "textures/floor.bmp", 512, 512);
    dp.DrawCuboidWithTexture(7.0, 0.01, 4.5, 0, -2.5, -0.5, floor_texture);

    //roof
    roof_texture[0] = roof_texture[1] = LoadTexture::LoadTextureImageFile("textures/shellColor - Front.bmp", 256, 256);
    roof_texture[5] = LoadTexture::LoadTextureImageFile("textures/shellColor - Left.bmp", 256, 256);
    roof_texture[3] = LoadTexture::LoadTextureImageFile("textures/shellColor - Right.bmp", 256, 256);
    roof_texture[4] = LoadTexture::LoadTextureImageFile("textures/roof.bmp", 256, 256);
    roof_texture[2] = LoadTexture::LoadTextureImageFile("textures/roof3.bmp", 256, 256);
    dp.DrawCuboidWithTexture(7.0, 0.4, 4.0, 0, 1.5, 0, roof_texture);
    roof_texture[2] = LoadTexture::LoadTextureImageFile("textures/roof4.bmp", 256, 256);
    dp.DrawCuboidWithTexture(3.5, 0.4, 2.0, 0, 1.5, -6, roof_texture);

    //shell_logo
    logo_texture[1] = LoadTexture::LoadTextureImageFile("textures/shellLogo - Front.bmp", 256, 256);
    glDeleteTextures(1, &logo_texture[3]);
    dp.DrawCuboidWithTexture(0.45, 0.45, 0.04, -4.9, 1.45, 4.05, logo_texture);
    logo_texture[3] = LoadTexture::LoadTextureImageFile("textures/shellLogo - Right.bmp", 256, 256);
    glDeleteTextures(1, &logo_texture[1]);
    dp.DrawCuboidWithTexture(0.04, 0.45, 0.45, 7.03, 1.45, 3.1, logo_texture);

    //radius, height, slices, dx, dy, dz, facing top 0

    //pillar
    glColor3ub(202, 204, 206); //light grey
    dp.DrawCylinder(0.15, 4.7, 10, -4.45, -2.5, 1.1, 0); //roof1
    dp.DrawCylinder(0.15, 4.7, 10, 0, -2.5, 1.1, 0);
    dp.DrawCylinder(0.15, 4.7, 10, 4.45, -2.5, 1.1, 0);
    dp.DrawCylinder(0.15, 4.7, 10, -4.45, -2.5, -2.6, 0); //roof2
    dp.DrawCylinder(0.15, 4.7, 10, 0, -2.5, -2.6, 0);
    dp.DrawCylinder(0.15, 4.7, 10, 4.45, -2.5, -2.6, 0);

    dp.DrawCylinder(0.15, 1.6, 10, (4.45 - 2.4), 0.5, -6.9, 0); //shop
    dp.DrawCylinder(0.15, 1.6, 10, -(4.45 - 2.4), 0.5, -6.9, 0);

    FreeCreatedTextures();
}

void DrawScene::DisplayTexturedScene_Stage()
{
    //stage
    stage_texture[4] = LoadTexture::LoadTextureImageFile("textures/tile.bmp", 512, 512);
    stage_texture[3] = stage_texture[5] = LoadTexture::LoadTextureImageFile("textures/gradientRed.bmp", 256, 256);
    stage_texture[0] = stage_texture[1] = LoadTexture::LoadTextureImageFile("textures/gradientRed - Front.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.45, 0.05, 1.29, -4.45, -2.51, 2, stage_texture);
    dp.DrawCuboidWithTexture(0.45, 0.05, 1.29, 0, -2.51, 2, stage_texture);
    dp.DrawCuboidWithTexture(0.45, 0.05, 1.29, 4.45, -2.51, 2, stage_texture);
    dp.DrawCuboidWithTexture(0.45, 0.05, 1.29, -4.45, -2.51, -1.75, stage_texture);
    dp.DrawCuboidWithTexture(0.45, 0.05, 1.29, 0, -2.51, -1.75, stage_texture);
    dp.DrawCuboidWithTexture(0.45, 0.05, 1.29, 4.45, -2.51, -1.75, stage_texture);

    //car_block_side
    SingleTexture(carBlockSide_texture, "textures/gradientRed.bmp", 256, 256);
    SingleTexture(carBlock_texture, "textures/gradientRed - Front.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, -4.45, -1.9, 3.4, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -5.3 + 0.5, -2.48, 3.4, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -4.6 + 0.5, -2.48, 3.4, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, -4.45, -1.9, 0.58, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -5.3 + 0.5, -2.48, 0.58, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -4.6 + 0.5, -2.48, 0.58, carBlockSide_texture);

    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, -4.45, -1.9, -0.34, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -5.3 + 0.5, -2.48, -0.34, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -4.6 + 0.5, -2.48, -0.34, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, -4.45, -1.9, -3.16, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -5.3 + 0.5, -2.48, -3.16, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -4.6 + 0.5, -2.48, -3.16, carBlockSide_texture);

    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 4.45, -1.9, 3.4, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 5.3 - 0.5, -2.48, 3.4, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 4.6 - 0.5, -2.48, 3.4, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 4.45, -1.9, 0.58, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 5.3 - 0.5, -2.48, 0.58, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 4.6 - 0.5, -2.48, 0.58, carBlockSide_texture);

    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 4.45, -1.9, -0.34, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 5.3 - 0.5, -2.48, -0.34, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 4.6 - 0.5, -2.48, -0.34, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 4.45, -1.9, -3.16, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 5.3 - 0.5, -2.48, -3.16, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 4.6 - 0.5, -2.48, -3.16, carBlockSide_texture);

    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 0, -1.9, 3.4, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 0.35, -2.48, 3.4, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -0.35, -2.48, 3.4, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 0, -1.9, 0.58, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 0.35, -2.48, 0.58, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -0.35, -2.48, 0.58, carBlockSide_texture);

    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 0, -1.9, -0.34, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 0.35, -2.48, -0.34, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -0.35, -2.48, -0.34, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.38, 0.03, 0.03, 0, -1.9, -3.16, carBlock_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, 0.35, -2.48, -3.16, carBlockSide_texture);
    dp.DrawCuboidWithTexture(0.03, 0.3, 0.03, -0.35, -2.48, -3.16, carBlockSide_texture);

    FreeCreatedTextures();
}

void DrawScene::DisplayTexturedScene_Machine()
{
    //textures[] -> 0-Back 1-front 2-bottom 3-right 4-top 5-left

    //machine_frame
    SingleTexture(machineFrame2_texture, "textures/machine/orangeYellowGradient.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.35, 0.08, 0.7, -4.45, -0.45, 2.15, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.35, 0.08, 0.7, 0, -0.45, 2.15, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.35, 0.08, 0.7, 4.45, -0.45, 2.15, machineFrame2_texture);
    
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, -4.45, -2.5, 2.65, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, -4.45, -2.5, 1.6, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 0, -2.5, 2.65, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 4.45, -2.5, 1.6, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 4.45, -2.5, 2.65, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 0, -2.5, 1.6, machineFrame2_texture);

    dp.DrawCuboidWithTexture(0.35, 0.08, 0.7, -4.45, -0.45, 2.15 -3.74, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.35, 0.08, 0.7, 0, -0.45, 2.15 - 3.74, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.35, 0.08, 0.7, 4.45, -0.45, 2.15 - 3.74, machineFrame2_texture);

    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, -4.45, -2.5, 2.65 - 3.74, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, -4.45, -2.5, 1.6 - 3.74, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 0, -2.5, 2.65 - 3.74, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 4.45, -2.5, 1.6 - 3.74, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 4.45, -2.5, 2.65 - 3.74, machineFrame2_texture);
    dp.DrawCuboidWithTexture(0.3, 1.1, 0.05, 0, -2.5, 1.6 - 3.74, machineFrame2_texture);

    //machine
    machine_texture[3] = LoadTexture::LoadTextureImageFile("textures/machine/machineRight.bmp", 256, 256);
    machine_texture[4] = LoadTexture::LoadTextureImageFile("textures/roof2.bmp", 256, 256);
    machine_texture[5] = LoadTexture::LoadTextureImageFile("textures/machine/machineLeft.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.30, 0.9, 0.5, -4.45, -2.4, 2.14, machine_texture);
    dp.DrawCuboidWithTexture(0.30, 0.9, 0.5, 0, -2.4, 2.14, machine_texture);
    dp.DrawCuboidWithTexture(0.30, 0.9, 0.5, 4.45, -2.4, 2.14, machine_texture);

    dp.DrawCuboidWithTexture(0.30, 0.9, 0.5, -4.45, -2.4, -1.6, machine_texture);
    dp.DrawCuboidWithTexture(0.30, 0.9, 0.5, 0, -2.4, -1.6, machine_texture);
    dp.DrawCuboidWithTexture(0.30, 0.9, 0.5, 4.45, -2.4, -1.6, machine_texture);

    //warningSign
    warningSignR_texture[3] = LoadTexture::LoadTextureImageFile("textures/machine/warningSignRight.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, -4.3, -1.35, 1.1, warningSignR_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, -4.3, -1.35, 1.1 - 3.7, warningSignR_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 0 + 0.15, -1.35, 1.1, warningSignR_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 0 + 0.15, -1.35, 1.1 - 3.7, warningSignR_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 4.3 + 0.3, -1.35, 1.1, warningSignR_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 4.3 + 0.3, -1.35, 1.1 - 3.7, warningSignR_texture);

    warningSignL_texture[5] = LoadTexture::LoadTextureImageFile("textures/machine/warningSignLeft.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, -4.6, -1.35, 1.1, warningSignL_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, -4.6, -1.35, 1.1 - 3.7, warningSignL_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 0 - 0.15, -1.35, 1.1, warningSignL_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 0 - 0.15, -1.35, 1.1 - 3.7, warningSignL_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 4.6 - 0.3, -1.35, 1.1, warningSignL_texture);
    dp.DrawCuboidWithTexture(0.01, 0.35, 0.3, 4.6 - 0.3, -1.35, 1.1 - 3.7, warningSignL_texture);

    //rubbishBin
    SingleTexture(rubbishBin_texture, "textures/machine/gray.bmp", 256, 256);
    rubbishBin_texture[3] = LoadTexture::LoadTextureImageFile("textures/machine/rubbishBinRight.bmp", 256, 256);
    rubbishBin_texture[5] = LoadTexture::LoadTextureImageFile("textures/machine/rubbishBinLeft.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.2, 0.35, 0.2, -4.45, -2.35, 2.95, rubbishBin_texture);
    dp.DrawCuboidWithTexture(0.2, 0.35, 0.2, -4.45, -2.35, 2.95 - 3.7, rubbishBin_texture);
    dp.DrawCuboidWithTexture(0.2, 0.35, 0.2, 4.45, -2.35, 2.95, rubbishBin_texture);
    dp.DrawCuboidWithTexture(0.2, 0.35, 0.2, 4.45, -2.35, 2.95 - 3.7, rubbishBin_texture);
    dp.DrawCuboidWithTexture(0.2, 0.35, 0.2, 0, -2.35, 2.95, rubbishBin_texture);
    dp.DrawCuboidWithTexture(0.2, 0.35, 0.2, 0, -2.35, 2.95 - 3.7, rubbishBin_texture);

    //advSign
    SingleTexture(advSign_texture, "textures/machine/advBody.bmp", 256, 256);
    advSign_texture[3] = LoadTexture::LoadTextureImageFile("textures/machine/advRight.bmp", 256, 256);
    advSign_texture[5] = LoadTexture::LoadTextureImageFile("textures/machine/advLeft.bmp", 256, 256);
    dp.DrawCuboidWithTexture(0.03, 0.45, 0.65, -4.45, -0.05, 1.89, advSign_texture);
    dp.DrawCuboidWithTexture(0.03, 0.45, 0.65, -4.45, -0.05, 1.89 - 3.7, advSign_texture);
    dp.DrawCuboidWithTexture(0.03, 0.45, 0.65, 4.45, -0.05, 1.89, advSign_texture);
    dp.DrawCuboidWithTexture(0.03, 0.45, 0.65, 4.45, -0.05, 1.89 - 3.7, advSign_texture);
    dp.DrawCuboidWithTexture(0.03, 0.45, 0.65, 0, -0.05, 1.89, advSign_texture);
    dp.DrawCuboidWithTexture(0.03, 0.45, 0.65, 0, -0.05, 1.89 - 3.7, advSign_texture);

    FreeCreatedTextures();
}

void DrawScene::DisplayTexturedScene_Shop()
{
    //textures[] -> 0-Back 1-front 2-bottom 3-right 4-top 5-left

    //shop_floor
    SingleTexture(floor_texture, "textures/floor.bmp", 512, 512);
    dp.DrawCuboidWithTexture(4.5, 0.01, 4.1, 0, -2.5, -8.1, floor_texture);

    //shop_roof
    roof_texture[1] = LoadTexture::LoadTextureImageFile("textures/shellColor2 - Front1.bmp", 512, 512);
    roof_texture[0] = LoadTexture::LoadTextureImageFile("textures/shellColor2 - Back.bmp", 256, 256);
    roof_texture[5] = LoadTexture::LoadTextureImageFile("textures/shellColor2 - Left.bmp", 256, 256);
    roof_texture[4] = LoadTexture::LoadTextureImageFile("textures/roof.bmp", 256, 256);
    roof_texture[3] = LoadTexture::LoadTextureImageFile("textures/shellColor2 - Right.bmp", 256, 256);
    roof_texture[2] = LoadTexture::LoadTextureImageFile("textures/ceiling2.bmp", 256, 256);
    dp.DrawCuboidWithTexture(4.6, 0.38, 1.3 + 1.5, 0, 0.42, -8.75, roof_texture);

    //shop
    shop_texture[1] = LoadTexture::LoadTextureImageFile("textures/shop/shop.bmp", 512, 512);
    shop_texture[0] = LoadTexture::LoadTextureImageFile("textures/shop/shopBack.bmp", 512, 512);
    shop_texture[2] = LoadTexture::LoadTextureImageFile("textures/tile.bmp", 512, 512);
    shop_texture[3] = LoadTexture::LoadTextureImageFile("textures/shop/shopRight.bmp", 512, 512);
    shop_texture[5] = LoadTexture::LoadTextureImageFile("textures/shop/shopLeft.bmp", 512, 512);
    shop_texture[4] = LoadTexture::LoadTextureImageFile("textures/shop/shopTop.bmp", 512, 512);
    dp.DrawCuboidWithTexture(4.0, 1.41, 1.1 + 1.5, 0, -2.44, -8.75, shop_texture);

    FreeCreatedTextures();
}