#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define stripeImageWidth 32
GLubyte stripeImage[4 * stripeImageWidth];

GLuint texNameTG;

void makeStripeImage(void){
	int j;
	for (j = 0; j < stripeImageWidth; j++){
		stripeImage[4*j] = (GLubyte)((j<=4)?255:0);
		stripeImage[4*j+1] = (GLubyte)((j > 4) ? 255 : 0);
		stripeImage[4 * j + 2] = (GLubyte)0;
		stripeImage[4 * j + 3] = (GLubyte)255;
	}
}

static GLfloat xequalzero[] = {1.0,0.0,0.0,0.0};
static GLfloat slanted[] = {1.0,1.0,1.0,0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

void initTG(void){

	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	makeStripeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glGenTextures(1, &texNameTG);
	glBindTexture(GL_TEXTURE_1D,texNameTG);

	glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage1D(GL_TEXTURE_1D,0,GL_RGBA,stripeImageWidth,0,GL_RGBA,GL_UNSIGNED_BYTE,stripeImage);


	/*Ĭ������£�
	��ͼģʽ��GL_MODULATE�� ������ģʽ�£�OpenGL����ݵ�ǰ�Ĺ���ϵͳ���������ɫ�ʺ�������
	�ڶ���ģʽ��GL_DECAL��������ģʽ�����еĹ���Ч��������Ч �ģ�OpenGL��������������ͼ����������ı��档
	�����GL_BLEND������ģʽ��������ʹ�û������������ģʽ�£����ǿ��԰ѵ�ǰ����ͬһ����
	ɫ��϶��õ�һ���µ��������ǿ��Ե���glTexEnvi���������õ�ǰ��ͼģʽ��*/
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	currentCoeff = xequalzero;
	currentGenMode = GL_OBJECT_LINEAR; //����ռ� ����������������   gl_eye_liner �ӵ������������� 
	currentPlane = GL_OBJECT_PLANE;
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,currentGenMode);
	glTexGenfv(GL_S,currentPlane,currentCoeff);

	glEnable(GL_TEXTURE_GEN_S); //s�����������������
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_CULL_FACE);//�����޳�����Ч��
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL); //ִ�к�ͼ���ܰѹⷴ�䵽��������
	glEnable(GL_NORMALIZE); //��������׼�����������
	glFrontFace(GL_CW); //GL_CW ��ʾ����˳��Ϊ˳ʱ�뷽��ı���Ϊ���档
	glCullFace(GL_BACK); //��ʾ���ö���α����ϵĹ��ա���Ӱ����ɫ���㼰��������������Ҫ����Ⱦ���㡣
	glMaterialf(GL_FRONT, GL_SHININESS, 64.0); 
}

void displayTG(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
		glRotatef(45.0,0.0,0.0,1.0);
		glBindTexture(GL_TEXTURE_1D,texNameTG);
		glutSolidTeapot(2.0);
	glPopMatrix();
	glFlush();
}

void reshapeTG(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-3.5,3.5,-3.5*(GLfloat)h/(GLfloat)w,3.5*(GLfloat)h/(GLfloat)w,-3.5,3.5);
	else
		glOrtho(-3.5*(GLfloat)w / (GLfloat)h, 3.5*(GLfloat)w / (GLfloat)h, -3.5, 3.5, -3.5, 3.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardTG(unsigned char key, int x, int y){
	switch (key)
	{
	case '1':
		currentGenMode = GL_EYE_LINEAR;
		currentPlane = GL_EYE_PLANE;
		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,currentGenMode);
		glTexGenfv(GL_S,currentPlane,currentCoeff);
		glutPostRedisplay();
		break;
	case '2':
		currentGenMode = GL_OBJECT_LINEAR;
		currentPlane = GL_OBJECT_PLANE;
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
		glTexGenfv(GL_S, currentPlane, currentCoeff);
		glutPostRedisplay();
		break;
	case '3':
		currentCoeff = slanted;
		glTexGenfv(GL_S, currentPlane, currentCoeff);
		glutPostRedisplay();
		break;
	case '4':
		currentCoeff = xequalzero;
		glTexGenfv(GL_S, currentPlane, currentCoeff);
		glutPostRedisplay();
		break;
	default:
		break;
	}
}