/*CGI Lab Test 2 by CHIN ZHEN YUAN B031910365*/
/*Press F1 to reset the view*/
/*Press QWEASDZX, arrow or PageUp/Down keys to control the view*/

#include "Main.h"
#include "LoadTexture.h"
#include "DrawScene.h"

#define PI 3.1415927
float lastx, lasty;
double rotate_x, rotate_y, rotate_z, scale;
double translate_x, translate_y, translate_z;

void init_value()
{
	rotate_x = 0;
	rotate_y = 0;
	rotate_z = 0;
	translate_x = 0;
	translate_y = -0.6;
	translate_z = 6.2; 
	scale = 1.0;
}

void reshape(int w, int h) 
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		translate_z += sin(rotate_y * PI / 180) * -0.05;
		translate_x += cos(rotate_y * PI / 180) * -0.05;
		break;
	case GLUT_KEY_RIGHT:
		translate_z += sin(rotate_y * PI / 180) * 0.05;
		translate_x += cos(rotate_y * PI / 180) * 0.05;
		break;
	case GLUT_KEY_UP:
		rotate_x -= 2.0; break; 
	case GLUT_KEY_DOWN:
		rotate_x += 2.0; break;
	case GLUT_KEY_PAGE_UP:
		rotate_z += 2.0; break;
	case GLUT_KEY_PAGE_DOWN:
		rotate_z -= 2.0; break;
	case GLUT_KEY_F1:
		init_value(); break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	float angle = 360 - rotate_y;
	switch (key)
	{
	case 'a': 
		rotate_y -= 2.0; break;
	case 'd': 
		rotate_y += 2.0; break;
	case 'w': //near
		translate_x += sin(angle * PI / 180) * -0.05;
		translate_z += cos(angle * PI / 180) * -0.05;
		break;
	case 's': //far
		translate_x += sin(angle * PI / 180) * 0.05;
		translate_z += cos(angle * PI / 180) * 0.05;
		break;
	case 'q': //up
		translate_y += 0.05; break;
	case 'e': //down
		translate_y -= 0.05; break;
	case 'z': //zoom in
		scale += 0.05; break;
	case 'x': //zoom out
		scale -= 0.05; break;
	case '27': //ESC
		exit(0); break;
	}
}

void mouseMovement(int x, int y) {

	int diffx = x - lastx;//check the difference between the current xand the last x position
	int diffy = y - lasty; //check the difference between the current yand the last y position

	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	rotate_x += (float)diffy; //set the xrot to xrot with the addition of the difference in the y position
	rotate_y += (float)diffx;    //set the xrot to yrot with the addition of the difference in the x position
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000.0 / 60.0, timer, 0);
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glEnable(GL_LIGHT1); //enable LIGHT1, our Ambient Light
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); //cause a material color to track the current color

}

void display(void) 
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	
	glLoadIdentity();

	//Lights
	GLfloat ambientLight[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat diffuseLight[] = { 1.0 ,1.0 ,1.0 , 1.0 }; //white diffuse light
	GLfloat specularLight[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat lightPosition[] = { 1.0, 1.0, 1.0, 1.0 }; //infinite light location

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glEnable(GL_COLOR_MATERIAL);
	
	glLineWidth(1.0f); //Set line width

	//Transform ->glRotated/glTranslated = current matrix * rotation/translation matrix
	glRotated(rotate_x, 1.0, 0.0, 0.0);
	glRotated(rotate_y, 0.0, 1.0, 0.0);
	glRotated(rotate_z, 0.0, 0.0, 1.0);
	glTranslated(-translate_x, -translate_y, -translate_z);
	glScalef(0.5 * scale, 0.5 * scale, 0.5 * scale);

	glutSolidSphere(3.0, 1.5, 0);
	//DrawScene ds;
	//ds.DisplayTexturedScene_Roof();
	//ds.DisplayTexturedScene_Stage();
	//ds.DisplayTexturedScene_Machine();
	//ds.DisplayTexturedScene_Shop();

	glutSwapBuffers();
}

int main(int argc, char** argv) 
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1080, 720);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("CGI Lab Test 2 by CHIN ZHEN YUAN B031910365");
	init();
	init_value();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	//glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutTimerFunc(1000.0 / 60.0, timer, 0);

	glutMainLoop();
}