#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

GLfloat ctrlpointsBS[4][4][3] = { -1.5,-1.5,4,-0.5,-1.5,2,
								  0.5,-1.5,-1,1.5,-1.5,2,
								  -1.5,-0.5,1,-0.5,-0.5,3,
								  0.5,-0.5,0,1.5,-0.5,-1,
								  -1.5,0.5,4,-0.5,0.5,0,
								  0.5,0.5,3,1.5,0.5,4,
								  -1.5,1.5,-2,-0.5,1.5,-2,
                                  0.5,1.5,0,1.5,1.5,-1};

GLfloat texpts[2][2][2] = { 
	{ { 0, 0 }, { 0, 1 } }, 
	{ { 1, 0 }, { 1, 1 } } 
};

#define imageWidthBS 64
#define imageHeightBS 64
GLubyte imageBS [3*imageWidthBS*imageHeightBS];

void makeImage(void){
	int i, j;
	float ti, tj;

	for (i = 0; i < imageWidthBS;i++){
		ti = 2 * 3.1415926 * i / imageWidthBS;
		for (j = 0; j < imageHeightBS; j++){
			tj = 2.0 *3.1415926 * j / imageHeightBS;

			imageBS[3 * (imageHeightBS*i + j)] = (GLubyte)127 * (1 + sin(ti));
			imageBS[3 * (imageHeightBS*i + j) + 1] = (GLubyte)127 * (1 + sin(2 + ti));
			imageBS[3 * (imageHeightBS*i + j) + 2] = (GLubyte)127 * (1 + sin(ti + tj));

		}
	}
}

void initBS(void){
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH); //线条的代码用flat  
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpointsBS[0][0][0]);//3维顶点 的一维求值器
	
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);//3维顶点 的一维求值器

	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(20, 0, 1, 20, 0, 1); //创建均匀分布网格  从0-1  中间20个分段
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_AUTO_NORMAL);

	makeImage();

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);//在这种模式下所有的光照效果都是无效的，OpenGL将仅依据纹理贴图来绘制物体的表面
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidthBS, imageHeightBS, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBS);

	glEnable(GL_TEXTURE_2D);
	/*光照
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat position[] = { 0, 0, 2, 1 };
	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat mat_specular[] = {1,1,1,1};
	GLfloat mat_shininess[] = { 50 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,position);

	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);*/
}

void displayBS(void){
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	
	//glPushMatrix();
	//glRotatef(85,1,1,1);

	/*******************网格自动均匀分布********************************/
	glEvalMesh2(GL_FILL,0,20,0,20);


	/*******************手动均匀分布********************************
	for (j = 0; j <= 8; j++){
		glBegin(GL_LINE_STRIP);		
			for (i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)i/30,(GLfloat)j/8);
		glEnd();

		glBegin(GL_LINE_STRIP);
			for (i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)j / 8, (GLfloat)i / 30);
		glEnd();	
	}*/

	/*
	glPointSize(5);
	glColor3f(1, 1, 0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			glVertex3fv(&ctrlpointsBS[i][j][0]);
		}
	}
	glEnd();*/

	//glPopMatrix();

	glFlush();
}

void reshapeBS(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-5, 5, -5 * (GLfloat)h / (GLfloat)w, 5 * (GLfloat)h / (GLfloat)w, -5, 5);
	else
		glOrtho(-5 * (GLfloat)h / (GLfloat)w, 5 * (GLfloat)h / (GLfloat)w, -5, 5, -5, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}