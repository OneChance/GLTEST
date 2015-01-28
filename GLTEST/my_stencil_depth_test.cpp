#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

void draw_sphere(){
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat pos[] = { 5, 5, 0, 1 };
	GLfloat ambient[] = {0,0,1,1};

	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);

	glColor3f(1,0,0);
	glPushMatrix();
		glTranslatef(0,0,2);
		glutSolidSphere(0.5,20,20);
	glPopMatrix();

}

void displayMySDT(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1,5,25);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5,0,6.5,0,0,0,0,1,0);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	draw_sphere();

	// 绘制一个平面镜。在绘制的同时注意设置模板缓冲。
	// 另外，为了保证平面镜之后的镜像能够正确绘制，在绘制平面镜时需要将深度缓冲区设置为只读的。
	// 在绘制时暂时关闭光照效果
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 1); //11111111
	glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
	
	glEnable(GL_STENCIL_TEST);

	glDisable(GL_LIGHTING);
	glColor3f(.5,.5,.5);
	glDepthMask(GL_FALSE); //将深度缓冲区设置为只读的
	glRectf(-1.5,-1.5,1.5,1.5);
	glDepthMask(GL_TRUE);

	// 绘制一个与先前球体关于平面镜对称的球体，注意光源的位置也要发生对称改变
	// 因为平面镜是在X轴和Y轴所确定的平面，所以只要Z坐标取反即可实现对称
	// 为了保证球体的绘制范围被限制在平面镜内部，使用模板测试
	glStencilFunc(GL_EQUAL,1,1);
	glScalef(1,1,-1);
	draw_sphere();

	glFlush();
}