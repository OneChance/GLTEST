#include "stdafx.h"
#include<glew.h>
#include<glut.h>

#define PAMPSIZE 16
#define PAMP1START 32
#define PAMP2START 48

float rotAngleI = 0.0;

void initAAI(){
	int i;
	for (i = 0; i < PAMPSIZE; i++){
		GLfloat shade;
		shade = (GLfloat)i / (GLfloat)PAMPSIZE;
		glutSetColor(PAMP1START+(GLint)i,0.,shade,0.);
		glutSetColor(PAMP2START+(GLint)i,0.,0.,shade);
	}

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_DONT_CARE);
	glLineWidth(2.);

	glClearIndex((GLfloat)PAMP1START);
}

void displayAAI(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glIndexi(PAMP1START);
	glPushMatrix();
	glRotatef(-rotAngleI, 0.0, 0.0, 0.1);
	glBegin(GL_LINES);
		glVertex2f(-0.5,0.5);
		glVertex2f(0.5,-0.5);
	glEnd();
	glPopMatrix();

	glIndexi(PAMP2START);
	glPushMatrix();
	glRotatef(rotAngleI, 0.0, 0.0, 0.1);
	glBegin(GL_LINES);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();
	glPopMatrix();

	glFlush();
}

void keyboardAAI(unsigned char key, int x, int y){
	switch (key)
	{
	case 'r':case 'R':
		rotAngleI += 20.;
		if (rotAngleI >= 360.)rotAngleI = 0.;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}