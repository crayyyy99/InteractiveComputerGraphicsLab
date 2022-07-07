#ifndef _DRAWPRIMITIVES_H  
#define _DRAWPRIMITIVES_H  

#include "Main.h"

class DrawPrimitives
{
public:
    //Cylinder
    double** GenerateFace(double radius, double z, int slices, int facing, bool half_phase);
    void JoinFaces(double** coord1, double** coord2, int count);
    void DrawFace(double** coord, int count);
    void TranslateVertex(double* source, double dx, double dy, double dz);
    void TranslateVertexArray(double** source, double count, double dx, double dy, double dz);
    void DeleteVertexArray(double** d, int size);

    void DrawCylinder(double radius, double height, int slices, double dx, double dy, double dz, int facing);
    
    //Cuboid
    void DrawCuboid(double w, double h, double l, double dx, double dy, double dz);
        
    void DrawCuboidWithTexture(double w, double h, double l, double dx, double dy, double dz, GLuint textures[6]);

};


#endif  