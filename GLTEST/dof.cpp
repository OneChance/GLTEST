#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

GLuint teapotList;

void initDof(void){
	GLfloat ambient[] = {0,0,0,0};
	GLfloat diffuse[] = {1,1,1,1};
	GLfloat specular[] = { 1, 1, 1, 1 };
	GLfloat position[] = { 0,3,3,0 };
	GLfloat lmodel_ambient[] = { .2, .2, .2, 1 };
	GLfloat local_view[] = { 0};

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient); //全局环境光RGBA强度
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view); //镜面反射夹角如何计算， 0表示平行于视口，朝向z轴

	glFrontFace(GL_CW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0,0,0,0);
	glClearAccum(0,0,0,0);

	teapotList = glGenLists(1);
	glNewList(teapotList, GL_COMPILE);
	glutSolidTeapot(0.5);
	glEndList();
}

void renderTeapot(GLfloat x,GLfloat y,GLfloat z,
							GLfloat ambr,GLfloat ambg,GLfloat ambb,
							GLfloat difr,GLfloat difg,GLfloat difb,
							GLfloat specr,GLfloat specg,GLfloat specb,
							GLfloat shine){
	GLfloat mat[4];

	glPushMatrix();
	glTranslatef(x,y,z);
	mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1;
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat);
	mat[0] = difr; mat[1] = difg; mat[2] = difb;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = specr; mat[1] = specg; mat[2] = specb;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT,GL_SHININESS,shine*128);
	glCallList(teapotList);
	glPopMatrix();
}

void displayDof(void){
	int jitter;
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT,viewport);
	glClear(GL_ACCUM_BUFFER_BIT);

	for (jitter = 0; jitter < 8; jitter++){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
}