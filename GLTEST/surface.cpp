#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#ifndef CALLBACK
#define CALLBACK
#endif

GLfloat ctlpointsSF[4][4][3];
int showpoints = 0;

GLUnurbsObj *theNurb;

void init_surface(void){
	int u, v;
	for (u = 0; u < 4; u++){
		for (v = 0; v < 4;v++){
			ctlpointsSF[u][v][0] = 2 * (u - 1.5);
			ctlpointsSF[u][v][1] = 2 * (v - 1.5);

			//���м����߱仯����ֵ
			if ((u == 1 || u == 2) && (v == 1 || v == 2))
				ctlpointsSF[u][v][2] = 3; 
			else
				ctlpointsSF[u][v][2] = -3;
		}
	}
}

void CALLBACK nurbsError(GLenum errorCode){
	const GLubyte *estring;
	estring = gluErrorString(errorCode);
	fprintf(stderr,"Nurbs Error:%s \n",estring);
	//exit(0);
}

void initSF(void){
	GLfloat mat_diffuse[] = {.7,.7,.7,1};
	GLfloat mat_specular[] = {1,1,1,1};
	GLfloat mat_shininess[] = { 100 };

	glClearColor(0,0,0,0);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	init_surface(); 

	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb,GLU_SAMPLING_TOLERANCE,25);//����������ľ�ϸ�̶�
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GL_FILL);
	gluNurbsCallback(theNurb, GLU_ERROR, (void(_stdcall *)())nurbsError);
}

void displaySF(void){
	GLfloat knots[8] = {0,0,0,0,1,1,1,1}; //���Ƶ���+���� һ����������4�����Ƶ� ���α��������� ����Ϊ4
	int i, j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(330,1,0,0);
	glScalef(0.5, 0.5, 0.5);

	gluBeginSurface(theNurb);

	/*
	 GLUnurbsObj * nobj, ���� //NURBS�������
��	 GLint sknot_count,       //s����ڵ���Ŀ
��	 GLfloat * sknot,         //s����ڵ�����ָ��
��	 GLint tknot_count,       //t����ڵ���Ŀ
��	 GLfloat * tknot,         //t����ڵ�����ָ��
��	 GLint s_stride,          //s������Ƶ����ݿ��
��	 GLint t_stride,          //t������Ƶ����ݿ��
��	 GLfloat * ctlarray,      //���Ƶ�����ָ��
��	 GLint sorder,            //s�����϶���ʽ����
��	 GLint torder,            //t�����϶���ʽ����
��	 GLenum type              //ȷ����ֵ������
	*/
	gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &ctlpointsSF[0][0][0], 4, 4, GL_MAP2_VERTEX_3);

	gluEndSurface(theNurb);

	if (showpoints){
		glPointSize(5);
		glDisable(GL_LIGHTING);
		glColor3f(1,1,0);
		glBegin(GL_POINTS);
		for (i = 0; i < 4;i++){
			for (j = 0; j < 4; j++){
				glVertex3f(ctlpointsSF[i][j][0], ctlpointsSF[i][j][1], ctlpointsSF[i][j][2]);
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}

	glPopMatrix();
	glFlush();
}

void reshapeSF(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLdouble)w / (GLdouble)h, 3, 8);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-5);
}

void keyboardSF(unsigned char key, int x, int y){
	switch(key){
	case 'c':case 'C':
		showpoints = !showpoints;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}