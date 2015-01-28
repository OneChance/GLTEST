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

	// ����һ��ƽ�澵���ڻ��Ƶ�ͬʱע������ģ�建�塣
	// ���⣬Ϊ�˱�֤ƽ�澵֮��ľ����ܹ���ȷ���ƣ��ڻ���ƽ�澵ʱ��Ҫ����Ȼ���������Ϊֻ���ġ�
	// �ڻ���ʱ��ʱ�رչ���Ч��
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 1); //11111111
	glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
	
	glEnable(GL_STENCIL_TEST);

	glDisable(GL_LIGHTING);
	glColor3f(.5,.5,.5);
	glDepthMask(GL_FALSE); //����Ȼ���������Ϊֻ����
	glRectf(-1.5,-1.5,1.5,1.5);
	glDepthMask(GL_TRUE);

	// ����һ������ǰ�������ƽ�澵�ԳƵ����壬ע���Դ��λ��ҲҪ�����ԳƸı�
	// ��Ϊƽ�澵����X���Y����ȷ����ƽ�棬����ֻҪZ����ȡ������ʵ�ֶԳ�
	// Ϊ�˱�֤����Ļ��Ʒ�Χ��������ƽ�澵�ڲ���ʹ��ģ�����
	glStencilFunc(GL_EQUAL,1,1);
	glScalef(1,1,-1);
	draw_sphere();

	glFlush();
}