/* 'a'-> gl_func_add 
   's'-> gl_func_subtract
   'r'-> gl_func_reverse_subtract
   'm'-> gl_min
   'x'-> gl_max
*/
#include<windows.h>
#include "stdafx.h"
#include<glew.h>
#include<glut.h>


void initBlend(void){
	glewInit();
	glClearColor(1.0,1.0,0.0,0.0);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);
}

void displayBlend(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	glRectf(-0.5,-0.5,0.5,0.5);
	glFlush();
}

void keyboardBlend(unsigned char key, int x, int y){

	switch (key)
	{		
	case 'a':case 'A':
		glBlendEquation(GL_FUNC_ADD);
		break;
	case 's':case 'S':
		glBlendEquation(GL_FUNC_SUBTRACT);
		break;
	case 'r':case 'R':
		glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
		break;
	case 'm':case 'M':
		glBlendEquation(GL_MIN);
		break;
	case 'x':case 'X':
		glBlendEquation(GL_MAX);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}