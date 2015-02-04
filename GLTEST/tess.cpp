#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#ifndef CALLBACK
#define CALLBACK
#endif

GLuint startList;
GLUtesselator *tobj;

GLdouble rect[4][3] = { 50, 50, 0, 200, 50, 0, 200, 200, 0, 50, 200, 0 };
GLdouble rect2[4][3] = { 30, 30, 0, 220, 30, 0, 220, 220, 0, 30, 220, 0 };

//GLdouble rect[4][3] = { 100, 80, 0, 100, 125, 0, 145, 125, 0, 145, 80, 0};

GLdouble tri[3][3] = {75,75,0,125,175,0,175,75,0};

//GLdouble tri[3][3] = { 175, 75, 0,125, 175, 0, 75, 75, 0 };

/*
    按顶点绘制方向，逆时针加1，顺时针-1

	glutessproperty方法的glu_tess_winding_rule 决定了填充方式

*/

GLdouble star[5][6] = {250,50,0,1,0,1,
					   325,200,0,1,1,0,
                       400,50,0,0,1,1,
                       250,150,0,1,0,0,
                       400,150,0,0,1,0};

void CALLBACK vertexCallback(GLvoid *vertex){
	const GLdouble *pointer;
	pointer = (GLdouble *)vertex;
	glColor3dv(pointer + 3);
	glVertex3dv(pointer);
}

void CALLBACK combineCallback(GLdouble coords[3], GLdouble *vertex_data[4], GLfloat weight[4], GLdouble **dataOut){
	GLdouble *vertex;
	int i;

	vertex = (GLdouble *)malloc(6 * sizeof(GLdouble));
	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];

	for (i = 3; i < 6; i++){
		vertex[i] = weight[0] * vertex_data[0][i] +
			weight[1] * vertex_data[1][i] +
			weight[2] * vertex_data[2][i] +
			weight[3] * vertex_data[3][i];
	}

	*dataOut = vertex;
}

void displayTess(void){

	glClearColor(0.0, 0.0, 0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	
	startList = glGenLists(2);

	
	tobj = gluNewTess();
	gluTessCallback(tobj,GLU_TESS_VERTEX,(void(_stdcall *)())glVertex3dv);
	gluTessCallback(tobj, GLU_TESS_BEGIN, (void(_stdcall *)())glBegin);
	gluTessCallback(tobj, GLU_TESS_END,(void(_stdcall *)())glEnd);

	glNewList(startList, GL_COMPILE);

		glShadeModel(GL_FLAT);
		glColor3f(1, 0, 0);
		
		gluTessBeginPolygon(tobj, NULL);
			
			gluTessBeginContour(tobj);
				gluTessVertex(tobj, tri[0], tri[0]);
				gluTessVertex(tobj, tri[1], tri[1]);
				gluTessVertex(tobj, tri[2], tri[2]);
			gluTessEndContour(tobj);

			gluTessBeginContour(tobj);
				gluTessVertex(tobj, rect[0], rect[0]);
				gluTessVertex(tobj, rect[1], rect[1]);
				gluTessVertex(tobj, rect[2], rect[2]);
				gluTessVertex(tobj, rect[3], rect[3]);
			gluTessEndContour(tobj);

			gluTessBeginContour(tobj);
			gluTessVertex(tobj, rect2[0], rect2[0]);
			gluTessVertex(tobj, rect2[1], rect2[1]);
			gluTessVertex(tobj, rect2[2], rect2[2]);
			gluTessVertex(tobj, rect2[3], rect2[3]);
			gluTessEndContour(tobj);

		gluTessEndPolygon(tobj);
		
		
		/*
		glBegin(GL_QUADS);
		glVertex3dv(rect2[0]);
		glVertex3dv(rect2[1]);
		glVertex3dv(rect2[2]);
		glVertex3dv(rect2[3]);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_QUADS);
		glVertex3dv(rect[0]);
		glVertex3dv(rect[1]);
		glVertex3dv(rect[2]);
		glVertex3dv(rect[3]);
		glEnd();
		
		glColor3f(0, 0, 1);
		glBegin(GL_TRIANGLES);
		glVertex3dv(tri[0]);
		glVertex3dv(tri[1]);
		glVertex3dv(tri[2]);
		glEnd();
		*/
	glEndList();

	//STAR
	gluTessCallback(tobj, GLU_TESS_VERTEX, (void(_stdcall *)())vertexCallback);
	gluTessCallback(tobj, GLU_TESS_BEGIN, (void(_stdcall *)())glBegin);
	gluTessCallback(tobj, GLU_TESS_END, (void(_stdcall *)())glEnd);
	gluTessCallback(tobj, GLU_TESS_COMBINE, (void(_stdcall *)())combineCallback);

	glNewList(startList + 1, GL_COMPILE);
		glShadeModel(GL_SMOOTH);
		gluTessProperty(tobj,GLU_TESS_WINDING_RULE,GLU_TESS_WINDING_POSITIVE);

		gluTessBeginPolygon(tobj, NULL);
			gluTessBeginContour(tobj);
				gluTessVertex(tobj,	star[0], star[0]);
				gluTessVertex(tobj, star[1], star[1]);
				gluTessVertex(tobj, star[2], star[2]);
				gluTessVertex(tobj, star[3], star[3]);
				gluTessVertex(tobj, star[4], star[4]);
			gluTessEndContour(tobj);
		gluTessEndPolygon(tobj);

	glEndList();

	glCallList(startList);
	glCallList(startList + 1);

	glFlush();
}



void reshapeTess(int w, int h){

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//正交投影，绘制2维图形
	if (w <= h){
		gluOrtho2D(-600, 600, -600* (GLfloat)h / (GLfloat)w, 600 * (GLfloat)h / (GLfloat)w);
	}
	else{
		gluOrtho2D(-600* (GLfloat)w / (GLfloat)h, 600 * (GLfloat)w / (GLfloat)h, -600, 600);
	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}