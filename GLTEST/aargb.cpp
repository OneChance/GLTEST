#include "stdafx.h"
#include<glew.h>
#include<glut.h>

float rotAngle = 0.0;

void initAAR(){
	GLfloat values[2];
	glGetFloatv(GL_LINE_WIDTH_GRANULARITY,values);
	printf("GL_LINE_WIDTH_GRANULARITY value is %3.1f \n",values[0]);
	glGetFloatv(GL_LINE_WIDTH_RANGE,values);
	printf("GL_LINE_WIDTH_RANGE value are %3.1f %3.1f \n", values[0],values[1]);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT,GL_DONT_CARE);
	glLineWidth(8);

	glClearColor(0.0,0.0,0.0,0.0);
}

void displayAAR(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glRotatef(-rotAngle,0.0,0.0,0.1);
	glBegin(GL_LINES);
		glVertex2f(-0.5,0.5);
		glVertex2f(0.5,-0.5);
	glEnd();
	glPopMatrix();

	glColor3f(0.0,0.0,1.0);
	glPushMatrix();
	glRotatef(rotAngle,0.0,0.0,0.1);
	glBegin(GL_LINES);
	glVertex2f(0.5, 0.5);
	glVertex2f(-0.5,-0.5);
	glEnd();
	glPopMatrix();

	glFlush();
}

void keyboardAAR(unsigned char key, int x, int y){
	switch (key)
	{
	case 'r':case 'R':
		rotAngle += 20.;
		if (rotAngle >= 360.)rotAngle = 0.;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}