#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define YELLOWMAT 1
#define BLUEMAT 2

void initSTENCIL(void){

	glClearColor(0.0, 0.0, 0.2, 0.0);
	
	GLfloat yellow_diffuse[] = { 0.7, 0.7, 0.0, 1.0 };
	GLfloat yellow_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat blue_diffuse[] = { 0.1, 0.1, 0.7, 1.0 };
	GLfloat blue_specular[] = { .1, 1.0, 1.0, 1.0 };

	GLfloat position_one[] = {1.0,1.0,1.0,0,0};

	glNewList(YELLOWMAT, GL_COMPILE);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,yellow_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,yellow_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,64);
	glEndList();

	glNewList(BLUEMAT, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 45);
	glEndList();

	glLightfv(GL_LIGHT0,GL_POSITION,position_one);

	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glClearStencil(0x0);//初始化模板值

	glEnable(GL_STENCIL_TEST);

}

void displaySTENCIL(void){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/*
	比较函数说明：此时模板值（菱形像素模板值为1，其他地方的像素模板值为0），参考值为1
	mask的二进制为:00000001,所以只比较模板值的最后一位（掩码为1的位置）  
	菱形像素模板值:00000001
	其他位置像素模板值:00000000

	如果可以通过测试，则在像素位置绘图，否则不绘制
	*/

	glStencilFunc(GL_EQUAL,1,1); //只在模板值为1的像素上绘制:菱形位置
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //保持像素模板值 （菱形像素模板值为1，其他地方的像素模板值为0）
	glCallList(BLUEMAT);
	glutSolidSphere(0.5,15,15);

	
	glStencilFunc(GL_NOTEQUAL, 1, 1); //只在模板值不为1的像素上绘制:菱形位置意外的位置

	glPushMatrix();
		glRotatef(45,0,0,1);
		glRotatef(45,0,1,0);
		glCallList(YELLOWMAT);
		glutSolidTorus(0.275,0.85,15,15);
		glPushMatrix();
			glRotatef(90.0,1.0,0.0,0.0);
			glutSolidTorus(0.275, 0.85, 15, 15);
		glPopMatrix();
	glPopMatrix();

	glFlush();
}

void reshapeSTENCIL(int w, int h){

	glViewport(0,0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//正交投影，绘制2维图形
	if (w <= h){
		gluOrtho2D(-3, 3, -3 * (GLfloat)h / (GLfloat)w, 3 * (GLfloat)h / (GLfloat)w);
	}
	else{
		gluOrtho2D(-3 * (GLfloat)w / (GLfloat)h, 3 * (GLfloat)w / (GLfloat)h ,- 3, 3);
	}

	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_STENCIL_BUFFER_BIT);//复位模板值   每个像素的模板值为0

	glStencilFunc(GL_ALWAYS,1,1);
	glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE); //设置模板值为1

	glBegin(GL_QUADS);  //绘制的菱形像素模板值为1，其他地方的像素模板值为0
		glVertex2f(-1,0);
		glVertex2f(0,1);
		glVertex2f(1, 0);
		glVertex2f(0, -1);
	glEnd();

	//切换到透视投影，准备绘制3维物体
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(GLfloat)w/(GLfloat)h,3,7);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -4);

}