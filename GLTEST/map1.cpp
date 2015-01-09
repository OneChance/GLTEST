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
	一种是GL_NEAREST。这个值指定了放大或缩小所采取的算法是最近邻法，即采样的像素是纹理映射进行缩放时，
	距离目标坐标（或称为中心像素的坐标）最近的像素。
	举个简单的例子。比如说对纹理做两倍的缩小，那么缩小后的纹理，第一个像素是原来的第一个像素，
	而第二像素则是原来第三个像素……对于两倍放大的情况下，
	放大后的第一个像素和第二个像素都是采原来第一个像素……
	最近邻算法的优势是速度快，所需的计算资源很小。而缺点是缩放的效果会显得很尖锐，在物体旋转时，往往会伴随有较严重的锯齿。

	第二个值是GL_LINEAR。这个值指定了纹理进行缩放时采用双线性插值（Bilinear Interpolate）算法。
	这个算法并不是直接将源纹理采到的像素搬到缩放后的纹理上。而是选中了目标像素（或称为中心像素）后，
	对其上下左右4个相邻的像素按照它们各自对目标像素所占的比重进行插值。
	这种插值算法的特点是运算量较大（将会用到三次乘法（或乘加）计算），但缩放效果会显得非常平滑
	*/
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);//第一维超出范围  repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//第一维超出范围  repeat
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);//纹理在映射到物体表面上时的放大效果 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//level:多重层次细节（多重纹理）
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