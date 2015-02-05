#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#ifndef CALLBACK
#define CALLBACK
#endif

GLuint startListQ;

void CALLBACK errorCallback(GLenum errorCode){
	const GLubyte *estring;
	estring = gluErrorString(errorCode);
	fprintf(stderr,"Quadric Error:%s \n",estring);
	exit(0);
}

void initQua(void){
	GLUquadricObj *qobj;
	GLfloat mat_ambient[] = {0.5,0.5,0.5,1.0};
	GLfloat mat_specular[] = {1,1,1,1};
	GLfloat mat_shininess[] = { 50 };
	GLfloat light_position[] = { 1,1,1,0 };
	GLfloat model_ambient[] = { .5, .5, .5, 1 };

	glClearColor(0,0,0,0);

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	startListQ = glGenLists(4);
	qobj = gluNewQuadric();
	gluQuadricCallback(qobj,GLU_ERROR,(void(_stdcall *)())errorCallback);

	gluQuadricDrawStyle(qobj,GLU_FILL);
	gluQuadricNormals(qobj,GLU_SMOOTH);
	glNewList(startListQ, GL_COMPILE);
		gluSphere(qobj,0.75,15,10);
	glEndList();

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_FLAT);
	glNewList(startListQ+1, GL_COMPILE);
		gluCylinder(qobj,0.3,0.3,1.0,15,5);
	glEndList();


	gluQuadricDrawStyle(qobj,GLU_LINE);
	gluQuadricNormals(qobj,GLU_NONE);
	glNewList(startListQ+2,GL_COMPILE);
		gluDisk(qobj,0.25,1,20,4);
	glEndList();

	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	gluQuadricNormals(qobj, GLU_NONE);
	glNewList(startListQ + 3, GL_COMPILE);
		gluPartialDisk(qobj,0,1,20,4,0,225);
	glEndList();

}

void displayQua(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glTranslatef(-1,-1,0);
	glCallList(startListQ);

	glShadeModel(GL_FLAT);
	glTranslatef(0,2,0);
	glPushMatrix();
	glRotatef(300,1,0,0);
	glCallList(startListQ+1);
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glColor3f(0,1,1);
	glTranslatef(2,-2,0);
	glCallList(startListQ+2);
	glColor3f(1,1,0);
	glTranslatef(0,2,0);
	glCallList(startListQ+3);

	glPopMatrix();
	glFlush();
}

void reshapeQua(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-2.5, 2.5, -2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w,-10,10);
	else
		glOrtho(-2.5*(GLfloat)h / (GLfloat)w, 2.5*(GLfloat)h / (GLfloat)w, -2.5, 2.5, -10, 10);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}
