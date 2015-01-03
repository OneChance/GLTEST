#include "stdafx.h"
#include<glew.h>
#include<glut.h>

#define MAXZ 8.0
#define MINZ -8.0
#define ZINC 0.4

float solidz = MAXZ;
float transparentZ = MINZ;
GLuint sphereList, cubeList;

void initA3(void){

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.15 };
	GLfloat mat_shininess[] = {100.0 };
	GLfloat position[] = {0.5,0.5,1.0,0.0};

	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	
	sphereList = glGenLists(1);
	glNewList(sphereList, GL_COMPILE);
		glutSolidSphere(0.4,16,16);
	glEndList();
	cubeList = glGenLists(1);
	glNewList(cubeList,GL_COMPILE);
		glutSolidCube(0.6);
	glEndList();
}

void displayA3(void){

	GLfloat mat_solid[] = {0.75,0.75,0.0,1.0};
	GLfloat mat_zero[] = {0.0,0.0,0.0,1.0};
	GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
	GLfloat mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glTranslatef(-0.15,-0.15,solidz);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_zero);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_solid);
		glCallList(sphereList);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15,0.15,transparentZ);
	glRotatef(15.0,1.0,1.0,0.0);
	glRotatef(30.0,0.0,1.0,0.0);
	glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_transparent);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glCallList(cubeList);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopMatrix();

	glutSwapBuffers();
}

void animate(void){
	if (solidz <= MINZ || transparentZ >= MAXZ){
		glutIdleFunc(NULL);
	}
	else{
		solidz -= ZINC;
		transparentZ += ZINC;
		glutPostRedisplay();
	}
}

void keyboardA3(unsigned char key, int x, int y){
	switch (key)
	{
	case 'a':case 'A':
		solidz = MAXZ;
		transparentZ = MINZ;
		glutIdleFunc(animate);
		break;
	case 'r':case 'R':
		solidz = MAXZ;
		transparentZ = MINZ;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}