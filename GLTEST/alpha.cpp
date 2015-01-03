#include<windows.h>
#include "stdafx.h"
#include<glew.h>
#include<glut.h>

static int leftFirst = GL_TRUE;

void initAlpha(void){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glClearColor(0.0,0.0,0.0,0.0);
}

void drawLeftTriangle(void){
	glBegin(GL_TRIANGLES);
		glColor4f(1.0, 1.0, 0.0, 0.75);
		glVertex3f(0.1,0.9,0.0);
		glVertex3f(0.1,0.1,0.0);
		glVertex3f(0.7,0.5,0.0);
	glEnd();
}

void drawRightTriangle(void){
	glBegin(GL_TRIANGLES);
	glColor4f(0.0, 1.0, 1.0, 0.75);
	glVertex3f(0.9, 0.9, 0.0);
	glVertex3f(0.3, 0.5, 0.0);
	glVertex3f(0.9, 1.0, 0.0);
	glEnd();
}

void displayAlpha(void){
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (leftFirst){
		drawLeftTriangle();
		drawRightTriangle();
	}
	else{
		drawRightTriangle();
		drawLeftTriangle();
	}
	glFlush();
}

void keyboardAlpha(unsigned char key,int x,int y){
	switch (key)			
	{
	case 't':case 'T':
		leftFirst = !leftFirst;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void reshapeAlpha(int w, int h){
	glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h){
		gluOrtho2D(0.0, 1.0, 0.0, (GLfloat)h / (GLfloat)w);
	}
	else{
		gluOrtho2D(0.0, 1.0*(GLfloat)w / (GLfloat)h, 0.0, 1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

