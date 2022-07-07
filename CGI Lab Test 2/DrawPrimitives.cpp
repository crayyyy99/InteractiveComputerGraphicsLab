#include "DrawPrimitives.h"
#include "LoadTexture.h"
#include "Main.h"

#define PI 3.1415927

GLfloat cuboid_v[8][3] = //clockwise
{ 
  { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 }, //front vertices -v0 = right bottom, v1 = left bottom
  { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } //back vertices -v3 = right bottom, v4 = left bottom
};

//      v6       v7
// v2       v3
//      v5       v4
// v1       v0

float texture_coord[4][2]={{ 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }}; //anticlockwise -> c0 = right bottom, c1 = right top

// c2  c1
// c3  c0

int orient[3][3] = {{ 0, 2, 1 }, { 0, 1, 2 }, { 1, 2, 0 }};

//Primitives

//Cylinder
double** DrawPrimitives::GenerateFace(double radius, double z, int slices, int facing, bool half_phase = false) //Function to generate faces of cylinder
{
    double** coord = new double* [slices];
    double angle = 360.0 / slices;
    double start_angle = half_phase ? angle / 2 : 0;
    for (int i = 0; i < slices; i++)
    {
        coord[i] = new double[3];
        double rs = radius * sin((angle * i + start_angle) * PI / 180.0);
        double rc = radius * cos((angle * i + start_angle) * PI / 180.0);
        coord[i][orient[facing][0]] = rs;
        coord[i][orient[facing][1]] = rc;
        coord[i][orient[facing][2]] = z;
    }
    return coord;
}

void DrawPrimitives::JoinFaces(double** coord1, double** coord2, int count) //Function to join faces of cylinder
{
    for (int i = 0; i < count; i++)
    {
        int j = (i + 1) < count ? i + 1 : 0;
        glBegin(GL_POLYGON);
        glVertex3d(coord1[i][0], coord1[i][1], coord1[i][2]);
        glVertex3d(coord1[j][0], coord1[j][1], coord1[j][2]);
        glVertex3d(coord2[j][0], coord2[j][1], coord2[j][2]);
        glVertex3d(coord2[i][0], coord2[i][1], coord2[i][2]);
        glEnd();
    }
}

void DrawPrimitives::DrawFace(double** coord, int count) //Function to draw faces of cylinder
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < count; i++) glVertex3d(coord[i][0], coord[i][1], coord[i][2]);
    glEnd();
}

void DrawPrimitives::TranslateVertex(double* source, double dx, double dy, double dz) //coordinate of 
{
    source[0] += dx;
    source[1] += dy;
    source[2] += dz;
}

void DrawPrimitives::TranslateVertexArray(double** source, double count, double dx, double dy, double dz) //dx - displacement x, dy - displacement y, dz - displacement z from the origin (object)
{
    for (int i = 0; i < count; i++)  { TranslateVertex(source[i], dx, dy, dz); }
}

void DrawPrimitives::DeleteVertexArray(double** d, int size) //clear vertex array
{
    for (int i = 0; i < size; i++) { delete[] d[i]; }
    delete[] d;
}

void DrawPrimitives::DrawCylinder(double radius, double height, int slices, double dx, double dy, double dz, int facing)
{
    double** coord1 = GenerateFace(radius, dy, slices, 0, true); //Facing top
    double** coord2 = GenerateFace(radius, dy + height, slices, 0, true); //Facing top
    TranslateVertexArray(coord1, slices, dx, 0, dz);
    TranslateVertexArray(coord2, slices, dx, 0, dz);
    DrawFace(coord1, slices);
    DrawFace(coord2, slices);
    JoinFaces(coord1, coord2, slices);
    DeleteVertexArray(coord1, slices);
    DeleteVertexArray(coord2, slices);
}

//Cuboid
void DrawPrimitives::DrawCuboid(double w, double h, double l, double dx, double dy, double dz)
{
    glBegin(GL_POLYGON); //front square
    for (int i = 0; i < 4; i++)
        glVertex3d(cuboid_v[i][0] * w + dx, cuboid_v[i][1] * h + h + dy, cuboid_v[i][2] * l + dz);
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 4; i < 8; i++) //back square
        glVertex3d(cuboid_v[i][0] * w + dx, cuboid_v[i][1] * h + h + dy, cuboid_v[i][2] * l + dz);
    glEnd();
    for (int i = 0; i < 4; i++)  //join together + displacement vector
    {
        int j = (i + 1) < 4 ? i + 1 : 0;
        glBegin(GL_POLYGON);
        glVertex3d(cuboid_v[i][0] * w + dx, cuboid_v[i][1] * h + h + dy, cuboid_v[i][2] * l + dz);
        glVertex3d(cuboid_v[j][0] * w + dx, cuboid_v[j][1] * h + h + dy, cuboid_v[j][2] * l + dz);
        glVertex3d(cuboid_v[j + 4][0] * w + dx, cuboid_v[j + 4][1] * h + h + dy, cuboid_v[j + 4][2] * l + dz);
        glVertex3d(cuboid_v[i + 4][0] * w + dx, cuboid_v[i + 4][1] * h + h + dy, cuboid_v[i + 4][2] * l + dz);
        glEnd();
    }
}

void DrawPrimitives::DrawCuboidWithTexture(double w, double h, double l, double dx, double dy, double dz, GLuint textures[6]) //6 faces
{
    //textures[] -> 0-Back 1-front 2-bottom 3-right 4-top 5-left

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        glTexCoord2d(texture_coord[i][0], texture_coord[i][1]);
        glVertex3d(cuboid_v[i][0] * w + dx, cuboid_v[i][1] * h + h + dy, cuboid_v[i][2] * l + dz);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, textures[1]); 
    glBegin(GL_POLYGON);
    for (int i = 4; i < 8; i++)
    {
        glTexCoord2d(texture_coord[i - 4][0], texture_coord[i - 4][1]);
        glVertex3d(cuboid_v[i][0] * w + dx, cuboid_v[i][1] * h + h + dy, cuboid_v[i][2] * l + dz);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    for (int i = 0; i < 4; i++) //l
    {
        int j = (i + 1) < 4 ? i + 1 : 0;
        glBindTexture(GL_TEXTURE_2D, textures[i + 2]);
        glBegin(GL_POLYGON);
        glTexCoord2d(texture_coord[0][0], texture_coord[0][1]);
        glVertex3d(cuboid_v[i][0] * w + dx, cuboid_v[i][1] * h + h + dy, cuboid_v[i][2] * l + dz);
        glTexCoord2d(texture_coord[1][0], texture_coord[1][1]);
        glVertex3d(cuboid_v[j][0] * w + dx, cuboid_v[j][1] * h + h + dy, cuboid_v[j][2] * l + dz);
        glTexCoord2d(texture_coord[2][0], texture_coord[2][1]);
        glVertex3d(cuboid_v[j + 4][0] * w + dx, cuboid_v[j + 4][1] * h + h + dy, cuboid_v[j + 4][2] * l + dz);
        glTexCoord2d(texture_coord[3][0], texture_coord[3][1]);
        glVertex3d(cuboid_v[i + 4][0] * w + dx, cuboid_v[i + 4][1] * h + h + dy, cuboid_v[i + 4][2] * l + dz);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, 0);

}
   







