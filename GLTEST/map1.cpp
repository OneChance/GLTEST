#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define checkImageWidth 64
#define checkImageHeight 64

#define subImageWidth 16
#define subImageHeight 16

GLubyte checkImage[checkImageHeight][checkImageWidth][4];
GLubyte subImage[subImageHeight][subImageWidth][4];

GLuint texName;

void makeCheckImageM1(void){
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++){
		for (j = 0; j < checkImageWidth; j++){
			c = (((i & 0x08) == 0) ^ ((j & 0x08) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	for (i = 0; i < subImageHeight; i++){
		for (j = 0; j < subImageWidth; j++){
			c = (((i & 0x04) == 0) ^ ((j & 0x04) == 0)) * 255;
			subImage[i][j][0] = (GLubyte)c;
			subImage[i][j][1] = (GLubyte)c;
			subImage[i][j][2] = (GLubyte)c;
			subImage[i][j][3] = (GLubyte)255;
		}
	}
}

void initM1(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	makeCheckImageM1();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1,&texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	/*
	һ����GL_NEAREST�����ֵָ���˷Ŵ����С����ȡ���㷨������ڷ���������������������ӳ���������ʱ��
	����Ŀ�����꣨���Ϊ�������ص����꣩��������ء�
	�ٸ��򵥵����ӡ�����˵����������������С����ô��С���������һ��������ԭ���ĵ�һ�����أ�
	���ڶ���������ԭ�����������ء������������Ŵ������£�
	�Ŵ��ĵ�һ�����غ͵ڶ������ض��ǲ�ԭ����һ�����ء���
	������㷨���������ٶȿ죬����ļ�����Դ��С����ȱ�������ŵ�Ч�����Եúܼ�����������תʱ������������н����صľ�ݡ�

	�ڶ���ֵ��GL_LINEAR�����ֵָ���������������ʱ����˫���Բ�ֵ��Bilinear Interpolate���㷨��
	����㷨������ֱ�ӽ�Դ����ɵ������ذᵽ���ź�������ϡ�����ѡ����Ŀ�����أ����Ϊ�������أ���
	������������4�����ڵ����ذ������Ǹ��Զ�Ŀ��������ռ�ı��ؽ��в�ֵ��
	���ֲ�ֵ�㷨���ص����������ϴ󣨽����õ����γ˷�����˼ӣ����㣩��������Ч�����Ե÷ǳ�ƽ��
	*/
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);//��һά������Χ  repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//��һά������Χ  repeat
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);//������ӳ�䵽���������ʱ�ķŴ�Ч�� 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//level:���ز��ϸ�ڣ���������
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,checkImageWidth,checkImageHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
}


void displayM1(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D,texName);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0,-1.0,0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
	glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0,-1.41421);

	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
}

void reshapeM1(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-3.6);
}

void keyboardM1(unsigned char key, int x, int y){
	switch (key)
	{
		case 's':case 'S':
			glBindTexture(GL_TEXTURE_2D,texName);
			glTexSubImage2D(GL_TEXTURE_2D,0,12,44,subImageWidth,subImageHeight,GL_RGBA,GL_UNSIGNED_BYTE,subImage);
			glutPostRedisplay();
			break;
		case 'r':case 'R':
			glBindTexture(GL_TEXTURE_2D, texName);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
			glutPostRedisplay();
			break;
		default:
			break;
	}
}