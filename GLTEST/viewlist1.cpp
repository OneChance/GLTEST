#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define M_PI 3.14159; 

GLuint theTorus;

void torus(int numc, int numt){
	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * (double)M_PI;
	for (i = 0; i < numc; i++){
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j < numt; j++){
			for (k = 1; k >= 0; k--){

				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (1 + .1*cos(s*twopi / numc)) * cos(t*twopi / numt);
				y = (1 + .1*cos(s*twopi / numc)) * sin(t*twopi / numt);
				z = .1 * sin(s*twopi/numc);

				glVertex3f(x,y,z);

			}
		}

		glEnd();	
	}

}

void initVL(void){
	theTorus = glGenLists(1);
	glNewList(theTorus,GL_COMPILE);
	torus(8, 25);
	glEndList();

	glShadeModel(GL_FLAT);
	glClearColor(0.0,0.0,0.0,0.0);
}

void displayVL(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glCallList(theTorus);
	glFlush();
}

void reshapeVL(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,(GLfloat)w/(GLfloat)h,1.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,10,0,0,0,0,1,0);
}

void keyboardVL(unsigned char key, int x, int y){
	switch (key){
		case 'x':case 'X':
			glRotatef(30,1,0,0);
			glutPostRedisplay();
			break;
		case 'y':case 'Y':
			glRotatef(30, 0, 1, 0);
			glutPostRedisplay();
			break;
		case 'i':case 'I':
			glLoadIdentity();
			gluLookAt(0,0,10,0,0,0,0,1,0);
			glutPostRedisplay();
			break;
	}
}