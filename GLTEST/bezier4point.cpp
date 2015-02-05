#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

GLfloat ctrlpoints[4][3] = {-4,-4,0,-2,4,0,2,-4,0,4,4,0};

void initB4(void){
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
	glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpoints[0][0]);//3维顶点 的一维求值器
	glEnable(GL_MAP1_VERTEX_3);
}

void displayB4(void){
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 30; i++){
			glEvalCoord1f((GLfloat)i/30);   //此处为u的取值   从0【开始】-1【结束】
		}
	glEnd();

	glPointSize(5);
	glColor3f(1,1,0);
	glBegin(GL_POINTS);
		for (i = 0; i < 4; i++){
			glVertex3fv(&ctrlpoints[i][0]);
		}
	glEnd();
	glFlush();
}

void reshapeB4(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-5, 5, -5*(GLfloat)h / (GLfloat)w, 5*(GLfloat)h / (GLfloat)w, -5, 5);
	else
		glOrtho(-5*(GLfloat)h / (GLfloat)w, 5*(GLfloat)h / (GLfloat)w, -5, 5, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}