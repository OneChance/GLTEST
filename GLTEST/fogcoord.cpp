#include "stdafx.h"
#include<glew.h>
#include<glut.h>

GLfloat f1, f2, f3;

void initFC(void){
	GLfloat fogColor[4] = {0.0,0.25,0.25,1.0};
	f1 = 1.f;
	f2 = 5.f;
	f3 = 10.f;
	glewInit();
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE,GL_EXP);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogf(GL_FOG_DENSITY,0.25);
	glHint(GL_FOG_HINT,GL_DONT_CARE);
	//启用显示雾坐标，雾颜色计算不受片段深度影响
	glFogi(GL_FOG_COORD_SRC,GL_FOG_COORD);
	glClearColor(0.0,0.25,0.25,1.0);
}

void displayFC(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f,0.75f,0.0f);
	glBegin(GL_TRIANGLES);
	glFogCoordf(f1);
	glVertex3f(2.0f,-2.0f,0.0f);
	glFogCoordf(f2);
	glVertex3f(-2.0f,0.0f,-5.0f);
	glFogCoordf(f3);
	glVertex3f(0.0f,2.0f,-10.0f);
	glEnd();
	glutSwapBuffers();
}

void keyboardFC(unsigned char key, int x, int y){
	switch (key)
	{
	case 'c':
		glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
		glutPostRedisplay();
		break;
	case 'C':
		glFogi(GL_FOG_COORD_SRC, GL_FOG_COORD);
		glutPostRedisplay();
		break;
	case '1':
		f1 += 0.25;
		glutPostRedisplay();
		break;
	case '2':
		f2 += 0.25;
		glutPostRedisplay();
		break;
	case '3':
		f3 += 0.25;
		glutPostRedisplay();
		break;
	case '8':
		if (f1 > 0.25){
			f1 -= 0.25;
			glutPostRedisplay();
		}
		break;
	case '9':
		if (f2 > 0.25){
			f2 -= 0.25;
			glutPostRedisplay();
	}
		break;
	case '0':
		if (f3 > 0.25){
			f3 -= 0.25;
			glutPostRedisplay();
		}
		break;
	case 's':
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0.0,0.0,-0.25);
		glutPostRedisplay();
		break; 
	case 'w':
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0.0, 0.0, 0.25);
		glutPostRedisplay();
	default:
		break;
	}
}