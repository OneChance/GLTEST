#include<windows.h>
#include "stdafx.h"
#include<glut.h>
#include <iostream>

using namespace std;

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

void initMethod(void){
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glClearColor(0.0, 0.0, 0.2, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void displayMethod(void){

	cout << "display...........";

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonOffset(1.0, 1.0);

	glPushMatrix();
		gluLookAt(2.0, 2.0, 0.0, 0.0, 0.0, -5.0, 0.0, 1.0, 0.0);

		glPushMatrix();
			glTranslatef(0.0,0.0,-5.0);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glutSolidCube(2.0);
			glDisable(GL_POLYGON_OFFSET_FILL);
			glColor3f(0.0, 1.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glutSolidCube(2.0);
		glPopMatrix();

	glPopMatrix();

	glFlush();
}

void reshapeMethod(int w, int h){

	cout << "reshape..........."; 

	glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//if (w <= h){
	//	glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w, -10, 10);
	//}
	//else{
	//	glOrtho(-2.5 * (GLfloat)w / (GLfloat)h, 2.5*(GLfloat)w / (GLfloat)h, -2.5, 2.5, -10, 10);
	//}

	gluPerspective(80.0f, w/h, 1.0, 200.0); //Í¸ÊÓÍ¶Ó° 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_position[] = { 2.0, 2.0, 0.0, 1.0 };
	glPushMatrix();
		glRotatef(45,0.,1.,0.);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();
}

void mouseMethod(int button, int state, int x, int y){

	/*
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			diffuseMaterial[0] += 0.1;
			if (diffuseMaterial[0] > 1.0){
				diffuseMaterial[0] = 0.0;
			}
			glColor4fv(diffuseMaterial);
			glutPostRedisplay();
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN){
			diffuseMaterial[1] += 0.1;
			if (diffuseMaterial[1] > 1.0){
				diffuseMaterial[1] = 0.0;
			}
			glColor4fv(diffuseMaterial);
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN){
			diffuseMaterial[2] += 0.1;
			if (diffuseMaterial[2] > 1.0){
				diffuseMaterial[2] = 0.0;
			}
			glColor4fv(diffuseMaterial);
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}*/
}
