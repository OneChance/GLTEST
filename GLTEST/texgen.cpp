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


	/*默认情况下，
	贴图模式是GL_MODULATE， 在这种模式下，OpenGL会根据当前的光照系统调整物体的色彩和明暗。
	第二种模式是GL_DECAL，在这种模式下所有的光照效果都是无效 的，OpenGL将仅依据纹理贴图来绘制物体的表面。
	最后是GL_BLEND，这种模式允许我们使用混合纹理。在这种模式下，我们可以把当前纹理同一个颜
	色混合而得到一个新的纹理。我们可以调用glTexEnvi函数来设置当前贴图模式：*/
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	currentCoeff = xequalzero;
	currentGenMode = GL_OBJECT_LINEAR; //物体空间 顶点坐标的线性组合   gl_eye_liner 视点坐标的线性组合 
	currentPlane = GL_OBJECT_PLANE;
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,currentGenMode);
	glTexGenfv(GL_S,currentPlane,currentCoeff);

	glEnable(GL_TEXTURE_GEN_S); //s坐标的纹理坐标生成
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_CULL_FACE);//开启剔除操作效果
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL); //执行后，图形能把光反射到各个方向
	glEnable(GL_NORMALIZE); //法向量标准化，方便计算
	glFrontFace(GL_CW); //GL_CW 表示顶点顺序为顺时针方向的表面为正面。
	glCullFace(GL_BACK); //表示禁用多边形背面上的光照、阴影和颜色计算及操作，消除不必要的渲染计算。
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