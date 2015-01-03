#include "stdafx.h"
#include<glew.h>
#include<glut.h>

GLint fogMode;

void initFog(void){
	GLfloat position[] = {0.5,0.5,3.0,0.0};
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat mat[3] = {0.1745,0.01175,0.01175};
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat);
	mat[0] = 0.61424;
	mat[1] = 0.04136;
	mat[2] = 0.04136;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat);
	mat[0] = 0.727811;
	mat[1] = 0.626959;
	mat[2] = 0.626959;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT,GL_SHININESS,0.6*128.0);

	glEnable(GL_FOG);

	GLfloat fogColor[4] = {0.5,0.5,0.5,1.0};
	fogMode = GL_EXP;
	glFogi(GL_FOG_MODE,fogMode);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogf(GL_FOG_DENSITY,0.35);
	glHint(GL_FOG_HINT,GL_DONT_CARE);
	glFogf(GL_FOG_START,1.0);
	glFogf(GL_FOG_END,5.0);

	glClearColor(0.5,0.5,0.5,1.0);
}

void renderSphere(GLfloat x, GLfloat y, GLfloat z){
	glPushMatrix();
	glTranslatef(x,y,z);
	glutSolidSphere(0.4,16,16);
	glPopMatrix();
}

void displayFog(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderSphere(-2.,-0.5,-1.0);
	renderSphere(-1.,-0.5,-2.0);
	renderSphere(0., -0.5, -3.0);
	renderSphere(1., -0.5, -4.0);
	renderSphere(2., -0.5, -5.0);
	glFlush();
}

void keyboardFog(unsigned char key, int x, int y){
	switch (key)
	{
	case 'f':case 'F':
		if (fogMode == GL_EXP){
			fogMode = GL_EXP2;
		}
		else if (fogMode == GL_EXP2){
			fogMode = GL_LINEAR;
		}
		else if (fogMode == GL_LINEAR){
			fogMode = GL_EXP;
		}

		glFogi(GL_FOG_MODE,fogMode);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}