#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

void init();
void init_value();
void reshape(int w, int h);
void specialKeys(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void mouseMovement(int x, int y);
void timer(int);

void display(void);